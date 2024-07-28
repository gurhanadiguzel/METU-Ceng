import 'dart:async';
import 'dart:convert';

import 'package:dio/dio.dart';
import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/data/repositories/data_user_repository.dart';
import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:expense_splitter_web_app/src/domain/entities/user.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/event_repository.dart';

class DataEventRepository implements EventRepository {
  static final _instance = DataEventRepository._internal();
  DataEventRepository._internal();
  factory DataEventRepository() => _instance;

  final StreamController<List<Event>?> _eventsStream = StreamController.broadcast();
  List<Event>? _events;
  bool _eventsFetched = false;
  String port = "5050";

  final dio = Dio();

  @override
  Future<void> addEvent(Event event) async {
    try {
      var response = await dio.request(
        '$endpoint:$port/add_event',
        options: Options(
          method: 'POST',
          headers: headers,
        ),
        data: event.toJson(),
      );

      if (response.statusCode == 201) {
        _events!.add(event);
        _eventsStream.add(_events!.toList());
        print(json.encode(response.data));
      } else {
        print(response.statusMessage);
      }
    } catch (e, st) {
      print(e);
      print(st);
      rethrow;
    }
  }

  @override
  Future<List<Event>> getEvents(User user) async {
    List<Event> events = [];
    try {
      var response = await dio.get(
        '$endpoint:$port/get_events',
        queryParameters: {"email": user.email},
        options: Options(headers: headers),
      );

      if (response.statusCode == 200) {
        List<Event> eventsList = [];

        dynamic eventData = json.decode(response.data)["events"];

        if (eventData is List) {
          for (var eventJson in eventData) {
            Event event = Event.fromJson(eventJson);
            eventsList.add(event);
          }
          print('Events are loaded successfully.');
        } else {
          print('Error: events data is not a list');
        }
        events = eventsList;
      } else {
        print(response.statusMessage);
      }
    } catch (e, st) {
      print(e);
      print(st);
      rethrow;
    }
    return events;
  }

  @override
  Future<void> addExpense(Event event, Expense expense) async {
    try {
      var requestData = {
        'eventId': event.id,
        'expense': expense.toJson(),
      };

      var response = await dio.post(
        '$endpoint:$port/add_expense',
        options: Options(
          headers: headers,
        ),
        data: json.encode(requestData),
      );

      if (response.statusCode == 201) {
        print('Expense added successfully.');
      } else {
        print('Error: ${response.statusMessage}');
      }
    } catch (e, st) {
      print('Error: $e');
      print('Stacktrace: $st');
      rethrow;
    }
  }

  void _initEventsStream() async {
    try {
      _events = await getEvents(DataUserRepository.user!);
      _eventsFetched = true;
      _eventsStream.add(_events!.toList());
    } catch (e, st) {
      print(e);
      print(st);
      rethrow;
    }
  }

  @override
  Stream<List<Event>?> getEventsStream() {
    try {
      if (!_eventsFetched) _initEventsStream();

      Future.delayed(Duration.zero).then((_) => _eventsStream.add(_events?.toList()));

      return _eventsStream.stream;
    } catch (e, st) {
      print(e);
      print(st);
      rethrow;
    }
  }
}

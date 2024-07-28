import 'dart:async';

import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/event_repository.dart';
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class DashboardController extends Controller {
  DashboardController(
    EventRepository eventRepository,
  ) : _eventRepository = eventRepository;

  final EventRepository _eventRepository;

  StreamSubscription? _eventsStream;

  List<Event>? events;
  @override
  void initListeners() {
    _eventsStream = _eventRepository.getEventsStream().listen(
      (event) {
        events = event;
        refreshUI();
      },
    );
  }

  @override
  void onDisposed() {
    if (_eventsStream != null) _eventsStream!.cancel();
    super.onDisposed();
  }

  double getTotalExpense(Event event) {
    double total = 0;
    for (Expense expense in event.expenses) {
      total += expense.amount;
    }
    return total;
  }
}

import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:expense_splitter_web_app/src/domain/entities/user.dart';

abstract class EventRepository {
  Future<void> addEvent(Event event);
  Future<List<Event>> getEvents(User user);
  Future<void> addExpense(Event event, Expense expense);
  Stream<List<Event>?> getEventsStream();
}

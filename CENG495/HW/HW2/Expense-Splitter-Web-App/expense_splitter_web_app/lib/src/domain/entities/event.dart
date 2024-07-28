import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:expense_splitter_web_app/src/domain/entities/participant.dart';

class Event {
  String id;
  String eventName;
  DateTime date;
  List<Participant> participants;
  List<Expense> expenses;
  String createdByEmail;

  Event({
    required this.id,
    required this.eventName,
    required this.date,
    required this.participants,
    required this.expenses,
    required this.createdByEmail,
  });

  Map<String, dynamic> toJson() {
    return {
      if (id != '') '_id': {"\$oid": id},
      'eventName': eventName,
      'date': date.toIso8601String(),
      'participants': participants.map((e) => e.toJson()).toList(),
      'expenses': expenses.map((e) => e.toJson()).toList(),
      'createdByEmail': createdByEmail,
    };
  }

  factory Event.fromJson(Map<String, dynamic> json) {
    return Event(
      id: json['_id']['\$oid'],
      eventName: json['eventName'],
      date: DateTime.parse(json['date']),
      participants: (json['participants'] as List).map((e) => Participant.fromJson(e)).toList(),
      expenses: (json['expenses'] as List).map((e) => Expense.fromJson(e)).toList(),
      createdByEmail: json['createdByEmail'],
    );
  }

  Event copyWith({
    String? id,
    String? eventName,
    DateTime? date,
    List<Participant>? participants,
    List<Expense>? expenses,
    String? createdByEmail,
  }) {
    return Event(
      id: id ?? this.id,
      eventName: eventName ?? this.eventName,
      date: date ?? this.date,
      participants: participants ?? this.participants,
      expenses: expenses ?? this.expenses,
      createdByEmail: createdByEmail ?? this.createdByEmail,
    );
  }
}

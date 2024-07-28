import 'package:expense_splitter_web_app/src/domain/entities/participant.dart';

class Expense {
  String expenseName;
  Participant payer;
  int amount;
  DateTime date;

  Expense({
    required this.expenseName,
    required this.payer,
    required this.amount,
    required this.date,
  });

  Map<String, dynamic> toJson() => {
        'expenseName': expenseName,
        'payer': payer.toJson(),
        'amount': amount,
        'date': date.toIso8601String(),
      };

  factory Expense.fromJson(Map<String, dynamic> json) => Expense(
        expenseName: json['expenseName'],
        payer: Participant.fromJson(json['payer']),
        amount: json['amount'],
        date: DateTime.parse(json['date']),
      );

  Expense copyWith({
    String? expenseName,
    Participant? payer,
    int? amount,
    DateTime? date,
  }) =>
      Expense(
        expenseName: expenseName ?? this.expenseName,
        payer: payer ?? this.payer,
        amount: amount ?? this.amount,
        date: date ?? this.date,
      );
}

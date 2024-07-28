import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:expense_splitter_web_app/src/domain/entities/participant.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/event_repository.dart';
import 'package:flutter/material.dart';
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class AddExpenseController extends Controller {
  AddExpenseController(
    EventRepository eventRepository,
    this.event,
  ) : _eventRepository = eventRepository;

  final EventRepository _eventRepository;
  final Event event;

  Participant? payer;
  String? expenseName;
  int? amount;
  DateTime? selectedDate;

  bool? isExpenseNameSetted;
  bool? isExpenseAmountSetted;
  bool? isExpenseParticipantSetted;
  bool? isNavigateEnable;

  TextEditingController dateController = TextEditingController();

  @override
  void initListeners() {}

  void addExpense() async {
    Expense expense = Expense(
      expenseName: expenseName!,
      payer: payer!,
      amount: amount!,
      date: selectedDate ?? DateTime.now(),
    );
    event.expenses.add(expense);
    await _eventRepository.addExpense(event, expense);
    refreshUI();
  }

  void setParticipant(String? value) {
    isNavigateEnable = null;
    for (Participant partic in event.participants) {
      if (partic.name == value) {
        payer = partic;
        isExpenseParticipantSetted = true;
        break;
      }
    }

    refreshUI();
  }

  void setExpenseName(String? value) {
    isNavigateEnable = null;
    expenseName = value;
    isExpenseNameSetted = true;
    refreshUI();
  }

  void setAmount(int? value) {
    isNavigateEnable = null;
    amount = value;
    isExpenseAmountSetted = true;
    refreshUI();
  }

  void checkNavigateEnable() {
    if (expenseName == null || expenseName == '') {
      isExpenseNameSetted = false;
      isNavigateEnable = false;
    }

    if (amount == null) {
      isExpenseAmountSetted = false;
      isNavigateEnable = false;
    }

    if (payer == null) {
      isExpenseParticipantSetted = false;
      isNavigateEnable = false;
    }

    if (isNavigateEnable != false) isNavigateEnable = true;

    refreshUI();
  }

  Future<void> selectDate(BuildContext context) async {
    DateTime? picked = await showDatePicker(
      context: context,
      initialDate: DateTime.now(),
      firstDate: DateTime(2000),
      lastDate: DateTime.now(),
    );

    if (picked != null) {
      dateController.text = picked.toString().split(" ")[0];
      selectedDate = picked;
    }
    refreshUI();
  }
}

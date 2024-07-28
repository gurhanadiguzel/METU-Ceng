import 'package:expense_splitter_web_app/src/app/pages/add_expense/add_expense_view.dart';
import 'package:expense_splitter_web_app/src/app/pages/dashboard/dashboard_view.dart';
import 'package:expense_splitter_web_app/src/app/pages/add_event/add_event_view.dart';
import 'package:expense_splitter_web_app/src/app/pages/event_details/event_details_view.dart';
import 'package:expense_splitter_web_app/src/app/pages/expenses/expenses_view.dart';
import 'package:expense_splitter_web_app/src/app/pages/register/register_view.dart';
import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:flutter/material.dart';

class WebNavigator {
  static Future<void> navigateToAddEventView(BuildContext context) async {
    await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => AddEventView(),
      ),
    );
  }

  static Future<void> navigateToAddExpenseView(BuildContext context, Event event) async {
    await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => AddExpenseView(event),
      ),
    );
  }

  static Future<void> navigateToRegisterView(BuildContext context) async {
    await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => RegisterView(),
      ),
    );
  }

  static Future<void> navigateToDashboardView(BuildContext context) async {
    await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => DashboardView(),
      ),
    );
  }

  static Future<void> navigateToEventDetailsView(BuildContext context, Event event) async {
    await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => EventDetailsView(event),
      ),
    );
  }

  static Future<void> navigateToExpensesView(BuildContext context, List<Expense> expenses) async {
    await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => ExpensesView(expenses),
      ),
    );
  }
}

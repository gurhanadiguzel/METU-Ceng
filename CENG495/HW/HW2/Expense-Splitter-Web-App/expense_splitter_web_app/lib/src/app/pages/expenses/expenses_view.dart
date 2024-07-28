import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/app/pages/expenses/expenses_controller.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/app_bar.dart';
import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:flutter/material.dart' hide View;
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';
import 'package:intl/intl.dart';

class ExpensesView extends View {
  final List<Expense> expenses;

  ExpensesView(this.expenses);

  @override
  State<StatefulWidget> createState() {
    return _ExpensesViewState(
      ExpensesController(),
      expenses,
    );
  }
}

class _ExpensesViewState extends ViewState<ExpensesView, ExpensesController> {
  _ExpensesViewState(
    super.controller,
    this.expenses,
  );

  final List<Expense> expenses;

  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();
  @override
  Widget get view {
    Size size = MediaQuery.of(context).size;

    return ControlledWidgetBuilder<ExpensesController>(
      builder: (context, controller) {
        return Scaffold(
          key: _scaffoldKey,
          appBar: AppBar(
            toolbarHeight: size.height * 0.12,
            title: const WebAppBar(),
            iconTheme: IconThemeData(color: kPrimaryColor),
          ),
          body: SingleChildScrollView(
            child: Container(
              color: kWhite,
              margin: EdgeInsets.symmetric(horizontal: 200, vertical: 50),
              child: Container(
                padding: EdgeInsets.symmetric(vertical: 15, horizontal: 50),
                decoration: BoxDecoration(
                  color: Colors.white,
                  borderRadius: BorderRadius.circular(10),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.3),
                      spreadRadius: 2,
                      blurRadius: 5,
                      offset: Offset(0, 3),
                    ),
                  ],
                ),
                child: Column(
                  children: [
                    Text(
                      "Expenses",
                      style: kTitleStyle(),
                    ),
                    Divider(height: 20, thickness: 2, color: Colors.grey),
                    SizedBox(height: 15),
                    for (Expense expense in expenses)
                      ExpenseWidget(
                        expense: expense,
                        controller: controller,
                      ),
                  ],
                ),
              ),
            ),
          ),
        );
      },
    );
  }
}

class ExpenseWidget extends StatelessWidget {
  const ExpenseWidget({
    required this.expense,
    required this.controller,
  });

  final Expense expense;
  final ExpensesController controller;

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: EdgeInsets.symmetric(vertical: 10, horizontal: 20),
      padding: EdgeInsets.all(15),
      decoration: BoxDecoration(
        color: Colors.white,
        borderRadius: BorderRadius.circular(10),
        boxShadow: [
          BoxShadow(
            color: Colors.grey.withOpacity(0.3),
            spreadRadius: 2,
            blurRadius: 5,
            offset: Offset(0, 3),
          ),
        ],
      ),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  'Expense Name: ${expense.expenseName}',
                  style: kSubtitleStyle(),
                ),
                SizedBox(height: 8),
                Text(
                  'Date: ${DateFormat.yMMMMd().format(expense.date)}',
                  style: TextStyle(
                    fontSize: 14,
                    color: Colors.grey,
                  ),
                ),
              ],
            ),
          ),
          SizedBox(width: 20),
          Column(
            crossAxisAlignment: CrossAxisAlignment.end,
            children: [
              Text(
                'Paid by: ${expense.payer.name}',
                style: kSubtitleStyle(),
              ),
              SizedBox(height: 8),
              Text(
                "${expense.amount} TL",
                style: TextStyle(
                  fontSize: 18,
                  fontWeight: FontWeight.bold,
                  color: Colors.green,
                ),
              ),
            ],
          ),
        ],
      ),
    );
  }
}

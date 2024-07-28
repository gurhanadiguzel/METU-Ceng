import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/app/navigator.dart';
import 'package:expense_splitter_web_app/src/app/pages/add_expense/add_expense_controller.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/app_bar.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/primary_button.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/web_text_field.dart';
import 'package:expense_splitter_web_app/src/data/repositories/data_event_repository.dart';
import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/participant.dart';
import 'package:flutter/material.dart' hide View;
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class AddExpenseView extends View {
  final Event event;

  AddExpenseView(this.event);

  @override
  State<StatefulWidget> createState() {
    return _AddExpenseViewState(
      AddExpenseController(
        DataEventRepository(),
        event,
      ),
      event,
    );
  }
}

class _AddExpenseViewState extends ViewState<AddExpenseView, AddExpenseController> {
  _AddExpenseViewState(super.controller, this.event);

  final Event event;

  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();
  @override
  Widget get view {
    Size size = MediaQuery.of(context).size;

    return ControlledWidgetBuilder<AddExpenseController>(
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
              width: size.width,
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
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    Text(
                      "Add Expense",
                      style: kTitleStyle(),
                    ),
                    Container(
                      width: (size.width - 40) / 2,
                      child: Divider(
                        height: 20,
                        thickness: 2,
                        color: Colors.grey,
                      ),
                    ),
                    SizedBox(height: 15),
                    Container(
                      width: (size.width - 40) / 2,
                      child: Row(
                        children: [
                          Flexible(
                            child: Container(
                              decoration: BoxDecoration(
                                border: Border.all(
                                  color: controller.isExpenseParticipantSetted == false ? Colors.red : Colors.white,
                                ),
                                borderRadius: BorderRadius.circular(10),
                              ),
                              child: DropdownButtonFormField<String>(
                                onChanged: (String? value) {
                                  controller.setParticipant(value);
                                },
                                items: [
                                  for (Participant participant in controller.event.participants)
                                    DropdownMenuItem(
                                      value: participant.name,
                                      child: Text(participant.name),
                                    ),
                                ],
                              ),
                            ),
                          ),
                          SizedBox(width: 25),
                          Flexible(
                            child: Text(
                              "paid for something.",
                              style: kSubtitleStyle(),
                            ),
                          ),
                        ],
                      ),
                    ),
                    SizedBox(height: 25),
                    WebTextField(
                      size: size,
                      title: "What For?",
                      hintText: "Ski Pass",
                      isObscure: false,
                      onChanged: (String input) {
                        controller.setExpenseName(input);
                      },
                      color: controller.isExpenseNameSetted == false ? Colors.red : null,
                    ),
                    SizedBox(height: 25),
                    WebTextField(
                      size: size,
                      title: "How Much?",
                      hintText: "Amount",
                      isObscure: false,
                      onChanged: (String input) {
                        controller.setAmount(int.parse(input));
                      },
                      color: controller.isExpenseAmountSetted == false ? Colors.red : null,
                    ),
                    SizedBox(height: 25),
                    Container(
                      width: (size.width - 40) / 2,
                      child: TextField(
                        controller: controller.dateController,
                        decoration: InputDecoration(
                          labelText: "DATE",
                          filled: true,
                          prefixIcon: Icon(
                            Icons.calendar_today,
                          ),
                          enabledBorder: OutlineInputBorder(
                            borderSide: BorderSide.none,
                          ),
                          focusedBorder: OutlineInputBorder(
                            borderSide: BorderSide(
                              color: kPrimaryColor,
                            ),
                          ),
                        ),
                        readOnly: true,
                        onTap: () {
                          controller.selectDate(context);
                        },
                      ),
                    ),
                    SizedBox(height: 25),
                    controller.isNavigateEnable == false
                        ? Text(
                            "Red areas cannot be blank!",
                            textAlign: TextAlign.start,
                            style: kSubtitleStyle(color: Colors.red),
                          )
                        : SizedBox(),
                    SizedBox(height: 25),
                    Container(
                      width: (size.width - 40) / 2,
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.end,
                        children: [
                          SizedBox(width: 25),
                          PrimaryButton(
                            text: 'Add',
                            onPressed: () {
                              controller.checkNavigateEnable();
                              if (controller.isNavigateEnable == true) {
                                controller.addExpense();
                                WebNavigator.navigateToEventDetailsView(context, event);
                              }
                            },
                            isEnabled: true,
                            isLoading: false,
                          ),
                        ],
                      ),
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

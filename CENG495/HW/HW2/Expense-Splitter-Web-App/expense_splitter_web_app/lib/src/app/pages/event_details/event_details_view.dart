import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/app/navigator.dart';
import 'package:expense_splitter_web_app/src/app/pages/event_details/event_details_controller.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/app_bar.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/primary_button.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/secondary_button.dart';
import 'package:expense_splitter_web_app/src/data/repositories/data_user_repository.dart';
import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:flutter/material.dart' hide View;
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class EventDetailsView extends View {
  final Event event;

  EventDetailsView(this.event);

  @override
  State<StatefulWidget> createState() {
    return _DashboardViewState(
      EventDetailsController(
        DataUserRepository(),
        event,
      ),
      event,
    );
  }
}

class _DashboardViewState extends ViewState<EventDetailsView, EventDetailsController> {
  _DashboardViewState(
    super.controller,
    this.event,
  );
  final Event event;

  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();
  @override
  Widget get view {
    Size size = MediaQuery.of(context).size;

    return ControlledWidgetBuilder<EventDetailsController>(
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
                    Column(
                      children: [
                        Text(
                          event.eventName,
                          style: kTitleStyle(),
                        ),
                        Divider(height: 20, thickness: 2, color: Colors.grey),
                        SizedBox(height: 15),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              'Overview',
                              style: TextStyle(
                                fontSize: 28,
                                fontWeight: FontWeight.w500,
                              ),
                            ),
                            Row(
                              mainAxisAlignment: MainAxisAlignment.end,
                              children: [
                                Container(
                                  width: 200,
                                  child: SecondaryButton(
                                    text: 'View All Expenses',
                                    onPressed: () {
                                      WebNavigator.navigateToExpensesView(context, controller.event.expenses);
                                    },
                                    isEnabled: true,
                                    isLoading: false,
                                  ),
                                ),
                                SizedBox(width: 20),
                                Container(
                                  width: 200,
                                  child: SecondaryButton(
                                    text: 'Add Expense',
                                    onPressed: () {
                                      WebNavigator.navigateToAddExpenseView(context, event);
                                    },
                                    isEnabled: true,
                                    isLoading: false,
                                  ),
                                ),
                              ],
                            ),
                          ],
                        ),
                        SizedBox(height: 20),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              "This event cost the group:",
                              style: kSubtitleStyle(),
                            ),
                            Text(
                              "${controller.getTotalExpensesAmount(event).toStringAsFixed(2)} TL",
                              style: kSubtitleStyle(),
                            ),
                          ],
                        ),
                        SizedBox(height: 20),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              "It cost you:",
                              style: kSubtitleStyle(),
                            ),
                            Text(
                              "${controller.calculateCostPerUser(event).toStringAsFixed(2)} TL",
                              style: kSubtitleStyle(),
                            ),
                          ],
                        ),
                        SizedBox(height: 20),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              "You have paid:",
                              style: kSubtitleStyle(),
                            ),
                            Text(
                              "${controller.getTotalPaidAmountForUsername(event, controller.currentUser!.username).toStringAsFixed(2)} TL",
                              style: kSubtitleStyle(),
                            ),
                          ],
                        ),
                        SizedBox(height: 20),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              controller.calculateDebtForUser(event, controller.currentUser!.username) > 0
                                  ? "You are owned:"
                                  : "You owe:",
                              style: kSubtitleStyle(),
                            ),
                            Text(
                              "${controller.calculateDebtForUser(event, controller.currentUser!.username).abs().toStringAsFixed(2)} TL",
                              style: kSubtitleStyle(),
                            ),
                          ],
                        ),
                        SizedBox(height: 20),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Flexible(
                              child: Column(
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: [
                                  Text(
                                    "Participants:",
                                    style: kSubtitleStyle(),
                                  ),
                                  SizedBox(height: 5),
                                  Column(
                                    crossAxisAlignment: CrossAxisAlignment.start,
                                    children: controller.event.participants
                                        .map(
                                          (p) => Text(
                                            '- ${p.name}',
                                            style: TextStyle(
                                              fontSize: 16,
                                              fontWeight: FontWeight.normal,
                                            ),
                                          ),
                                        )
                                        .toList(),
                                  ),
                                ],
                              ),
                            ),
                          ],
                        ),
                      ],
                    ),
                    SizedBox(height: 20),
                    Divider(height: 20, thickness: 2, color: Colors.grey),
                    SizedBox(height: 20),
                    Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Row(
                          children: [
                            Text(
                              "How to settle all debts",
                              style: TextStyle(
                                fontSize: 28,
                                fontWeight: FontWeight.w500,
                              ),
                            ),
                          ],
                        ),
                        SizedBox(height: 20),
                        for (String debt in controller.getAllDebts())
                          Container(
                            padding: EdgeInsets.symmetric(vertical: 5, horizontal: 10),
                            child: Text(
                              "- $debt",
                              style: kSubtitleStyle(),
                            ),
                          ),
                        SizedBox(height: 20),
                      ],
                    ),
                    PrimaryButton(
                      text: "Return to Dashboard",
                      onPressed: () {
                        WebNavigator.navigateToDashboardView(context);
                      },
                      isEnabled: true,
                      isLoading: false,
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

import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/app/navigator.dart';
import 'package:expense_splitter_web_app/src/app/pages/dashboard/dashboard_controller.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/app_bar.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/primary_button.dart';
import 'package:expense_splitter_web_app/src/data/repositories/data_event_repository.dart';
import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:flutter/material.dart' hide View;
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';
import 'package:intl/intl.dart';

class DashboardView extends View {
  @override
  State<StatefulWidget> createState() {
    return _DashboardViewState(
      DashboardController(
        DataEventRepository(),
      ),
    );
  }
}

class _DashboardViewState extends ViewState<DashboardView, DashboardController> {
  _DashboardViewState(super.controller);

  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();
  @override
  Widget get view {
    Size size = MediaQuery.of(context).size;

    return ControlledWidgetBuilder<DashboardController>(
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
              color: kBackgroundColor,
              margin: EdgeInsets.symmetric(horizontal: 200, vertical: 50),
              child: Container(
                padding: EdgeInsets.symmetric(vertical: 15, horizontal: 50),
                decoration: BoxDecoration(
                  color: kWhite,
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
                      "Dashboard",
                      style: kTitleStyle(),
                    ),
                    Divider(height: 20, thickness: 2, color: Colors.grey),
                    SizedBox(height: 15),
                    controller.events != null
                        ? Column(
                            children: controller.events!.map(
                              (event) {
                                return EventWidget(
                                  event: event,
                                  controller: controller,
                                );
                              },
                            ).toList(),
                          )
                        : CircularProgressIndicator(),
                    SizedBox(height: 20),
                    PrimaryButton(
                      onPressed: () {
                        WebNavigator.navigateToAddEventView(context);
                      },
                      text: "Add Event",
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

class EventWidget extends StatelessWidget {
  const EventWidget({
    required this.event,
    required this.controller,
  });

  final Event event;
  final DashboardController controller;

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        WebNavigator.navigateToEventDetailsView(context, event);
      },
      child: Container(
        margin: EdgeInsets.symmetric(vertical: 10, horizontal: 20),
        padding: EdgeInsets.all(20),
        decoration: BoxDecoration(
          color: Colors.white,
          borderRadius: BorderRadius.circular(15),
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
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Expanded(
              flex: 2,
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    event.eventName,
                    style: TextStyle(
                      fontSize: 18,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  SizedBox(height: 5),
                  Text(
                    'Date: ${DateFormat.yMMMMd().format(event.date)}',
                    style: TextStyle(
                      fontSize: 14,
                      color: Colors.grey,
                    ),
                  ),
                  SizedBox(height: 5),
                  Text(
                    'Participants: ${event.participants.length}',
                    style: TextStyle(
                      fontSize: 14,
                      color: Colors.grey,
                    ),
                  ),
                ],
              ),
            ),
            SizedBox(width: 20),
            Expanded(
              flex: 1,
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.end,
                children: [
                  Text(
                    'Total Expense:',
                    style: TextStyle(
                      fontSize: 14,
                      color: Colors.grey,
                    ),
                  ),
                  SizedBox(height: 5),
                  Text(
                    '${controller.getTotalExpense(event)} TL',
                    style: TextStyle(
                      fontSize: 18,
                      fontWeight: FontWeight.bold,
                      color: Colors.green,
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}

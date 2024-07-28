import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/app/pages/add_event/add_event_controller.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/app_bar.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/primary_button.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/web_text_field.dart';
import 'package:expense_splitter_web_app/src/data/repositories/data_event_repository.dart';
import 'package:expense_splitter_web_app/src/data/repositories/data_user_repository.dart';
import 'package:flutter/material.dart' hide View;
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class AddEventView extends View {
  @override
  State<StatefulWidget> createState() {
    return _AddEventViewState(
      AddEventController(
        DataEventRepository(),
        DataUserRepository(),
      ),
    );
  }
}

class _AddEventViewState extends ViewState<AddEventView, AddEventController> {
  _AddEventViewState(super.controller);

  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  Widget get view {
    Size size = MediaQuery.of(context).size;

    return ControlledWidgetBuilder<AddEventController>(
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
                  children: [
                    Text(
                      "Add Event",
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
                    WebTextField(
                      size: size,
                      title: "Event Name",
                      hintText: "Event Name",
                      isObscure: false,
                      onChanged: (String input) {
                        controller.setEventName(input);
                      },
                      color: controller.isEventNameSetted == false ? Colors.red : null,
                    ),
                    SizedBox(height: 25),
                    Container(
                      width: (size.width - 40) / 2,
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                            "Currency",
                            textAlign: TextAlign.left,
                            style: TextStyle(
                              fontSize: 14,
                              fontWeight: FontWeight.w400,
                            ),
                          ),
                          SizedBox(height: 6),
                          TextFormField(
                            enabled: false,
                            style: TextStyle(height: 1),
                            obscureText: false,
                            decoration: InputDecoration(
                              disabledBorder: OutlineInputBorder(
                                borderSide: BorderSide(color: kBorderColor),
                                borderRadius: BorderRadius.circular(10),
                              ),
                              filled: false,
                              hintStyle: TextStyle(color: kBlackHint),
                              hintText: "Turkish Lira",
                            ),
                          ),
                        ],
                      ),
                    ),
                    SizedBox(height: 50),
                    for (int i = 0; i < controller.participants.length; i++)
                      Participants(
                        size: size,
                        index: i,
                        controller: controller,
                      ),
                    controller.isNavigateEnable == false
                        ? Text(
                            "Red areas cannot be blank!",
                            textAlign: TextAlign.start,
                            style: kSubtitleStyle(color: Colors.red),
                          )
                        : SizedBox(),
                    SizedBox(height: 25),
                    PrimaryButton(
                      text: "+ Add New Person",
                      onPressed: () {
                        controller.addParticipant();
                      },
                      isEnabled: true,
                      isLoading: false,
                    ),
                    SizedBox(height: 25),
                    PrimaryButton(
                      text: "Add Event",
                      onPressed: () {
                        controller.checkNavigateEnable();
                        if (controller.isNavigateEnable == true) {
                          controller.addEvent();
                          Navigator.pop(context);
                        }
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

class Participants extends StatelessWidget {
  const Participants({
    super.key,
    required this.index,
    required this.size,
    required this.controller,
  });

  final Size size;
  final int index;
  final AddEventController controller;

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        index == 0
            ? Column(
                children: [
                  Container(
                    width: (size.width - 40) / 2,
                    child: Column(
                      children: [
                        Container(
                          width: (size.width - 40) / 2,
                          child: Text(
                            "You",
                            textAlign: TextAlign.left,
                            style: TextStyle(
                              fontSize: 14,
                              fontWeight: FontWeight.w400,
                            ),
                          ),
                        ),
                        SizedBox(height: 6),
                        TextFormField(
                          enabled: false,
                          style: TextStyle(height: 1),
                          obscureText: false,
                          decoration: InputDecoration(
                            disabledBorder: OutlineInputBorder(
                              borderSide: BorderSide(color: kBorderColor),
                              borderRadius: BorderRadius.circular(10),
                            ),
                            filled: false,
                            hintStyle: TextStyle(color: kBlackHint),
                            hintText: controller.user!.username,
                          ),
                        ),
                      ],
                    ),
                  ),
                ],
              )
            : WebTextField(
                size: size,
                title: "Person ${index + 1}",
                hintText: "Name",
                isObscure: false,
                onChanged: (String input) {
                  controller.setParticipantName(input, index);
                },
                color: controller.isParticipantsSetted[index] == false ? Colors.red : null,
              ),
        SizedBox(height: 25),
      ],
    );
  }
}

import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/app/pages/register/register_controller.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/app_bar.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/primary_button.dart';
import 'package:expense_splitter_web_app/src/app/pages/widgets/web_text_field.dart';
import 'package:expense_splitter_web_app/src/data/repositories/data_user_repository.dart';
import 'package:flutter/material.dart' hide View;
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class RegisterView extends View {
  @override
  State<StatefulWidget> createState() {
    return _RegisterViewState(
      RegisterController(
        DataUserRepository(),
      ),
    );
  }
}

class _RegisterViewState extends ViewState<RegisterView, RegisterController> {
  _RegisterViewState(super.controller);

  @override
  Widget get view {
    final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();
    Size size = MediaQuery.of(context).size;
    return ControlledWidgetBuilder<RegisterController>(
      builder: (context, controller) {
        return Scaffold(
          key: _scaffoldKey,
          appBar: AppBar(
            toolbarHeight: size.height * 0.12,
            title: const WebAppBar(),
            iconTheme: IconThemeData(color: kPrimaryColor),
          ),
          body: Container(
            width: size.width,
            height: size.height,
            child: Column(
              children: [
                Expanded(
                  child: SingleChildScrollView(
                    physics: BouncingScrollPhysics(
                      parent: AlwaysScrollableScrollPhysics(),
                    ),
                    child: Container(
                      margin: EdgeInsets.all(20),
                      child: Row(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          Container(
                            width: (size.width - 40) / 4,
                            child: Column(
                              children: [
                                Text(
                                  "Log in",
                                  textAlign: TextAlign.left,
                                  style: kTitleStyle(),
                                ),
                                Container(
                                  padding: EdgeInsets.only(top: 10),
                                  width: size.width - 60,
                                  child: Text(
                                    "Welcome back!",
                                    textAlign: TextAlign.center,
                                    style: kSubtitleStyle(),
                                  ),
                                ),
                                SizedBox(height: 50),
                                WebTextField(
                                  size: size,
                                  title: "Email Address",
                                  hintText: "Your email",
                                  isObscure: false,
                                  onChanged: controller.setEmailLogin,
                                  color: (controller.isLoginValid == false) ? Colors.red : null,
                                ),
                                SizedBox(height: 20),
                                WebTextField(
                                  size: size,
                                  title: "Password",
                                  hintText: "Your password",
                                  isObscure: true,
                                  onChanged: controller.setPasswordLogin,
                                  color: (controller.isLoginValid == false) ? Colors.red : null,
                                ),
                                SizedBox(height: 15),
                                Container(
                                  width: size.width - 40,
                                  child: Text(
                                    "Forgot password?",
                                    textAlign: TextAlign.right,
                                    style: TextStyle(
                                      fontSize: 14,
                                      fontWeight: FontWeight.w400,
                                    ),
                                  ),
                                ),
                                SizedBox(height: 50),
                                PrimaryButton(
                                  text: "Log in",
                                  onPressed: () {
                                    controller.logIn(context);
                                  },
                                  isEnabled: controller.isFieldsAreInitializedForLogin(),
                                  isLoading: controller.isLoading,
                                ),
                                SizedBox(height: 25),
                                if (controller.isLoginValid == false)
                                  Text(
                                    "User information is not correct!",
                                    textAlign: TextAlign.start,
                                    style: kSubtitleStyle(),
                                  ),
                                SizedBox(height: 40),
                              ],
                            ),
                          ),
                          Container(
                            width: 1,
                            height: size.height - 200,
                            color: kBlackHint,
                          ),
                          Container(
                            width: (size.width - 40) / 4,
                            child: Column(
                              children: [
                                Text(
                                  "Create Account",
                                  textAlign: TextAlign.center,
                                  style: kTitleStyle(),
                                ),
                                Container(
                                  padding: EdgeInsets.only(top: 10),
                                  width: size.width - 60,
                                  child: Text(
                                    "Welcome to Expense Splitter!",
                                    textAlign: TextAlign.center,
                                    style: kSubtitleStyle(),
                                  ),
                                ),
                                SizedBox(height: 50),
                                WebTextField(
                                  size: size,
                                  title: "Username",
                                  hintText: "Your username",
                                  isObscure: false,
                                  onChanged: controller.setUsername,
                                  color: controller.isUsernameAvaliable == false ? Colors.red : null,
                                ),
                                SizedBox(height: 20),
                                WebTextField(
                                  size: size,
                                  title: "Email",
                                  hintText: "Your email",
                                  isObscure: false,
                                  onChanged: controller.setEmail,
                                  color: controller.isEmailValid == false ? Colors.red : null,
                                ),
                                SizedBox(height: 20),
                                WebTextField(
                                  size: size,
                                  title: "Password",
                                  hintText: "Your password",
                                  isObscure: true,
                                  onChanged: controller.setPassword,
                                ),
                                SizedBox(height: 20),
                                WebTextField(
                                  size: size,
                                  title: "Password Again",
                                  hintText: "Your Password",
                                  isObscure: true,
                                  onChanged: controller.setPasswordAgain,
                                  color: controller.isPasswordsMatch == false ? Colors.red : null,
                                ),
                                SizedBox(height: 20),
                                SizedBox(height: 20),
                                GestureDetector(
                                  onTap: controller.toggleTermsAndPolicy,
                                  child: Row(
                                    children: [
                                      SizedBox(width: 10),
                                      Checkbox(
                                        value: controller.termsAndPrivacyAccepted,
                                        onChanged: (_) {
                                          controller.toggleTermsAndPolicy();
                                        },
                                      ),
                                      Flexible(
                                        child: Container(
                                          child: Text(
                                            "I accept the terms and privacy policy",
                                            style: TextStyle(
                                              fontWeight: FontWeight.w400,
                                              fontSize: 14,
                                            ),
                                          ),
                                        ),
                                      ),
                                    ],
                                  ),
                                ),
                                SizedBox(height: 40),
                                PrimaryButton(
                                  text: "Sign Up",
                                  onPressed: () {
                                    controller.signUp(context);
                                  },
                                  isEnabled: controller.isFieldsAreInitializedForRegister(),
                                  isLoading: controller.isLoading,
                                ),
                                SizedBox(height: 25),
                                if (controller.isEmailValid == false)
                                  Text(
                                    "Email is not a valid email!",
                                    textAlign: TextAlign.start,
                                    style: kSubtitleStyle(),
                                  ),
                                if (controller.isPasswordsMatch == false)
                                  Text(
                                    "Passwords are not the same!",
                                    textAlign: TextAlign.start,
                                    style: kSubtitleStyle(),
                                  ),
                              ],
                            ),
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ),
        );
      },
    );
  }
}

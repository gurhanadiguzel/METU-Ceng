import 'dart:convert';
import 'package:crypto/crypto.dart';
import 'package:expense_splitter_web_app/src/app/navigator.dart';
import 'package:expense_splitter_web_app/src/data/exceptions/invalid_login_exception.dart';
import 'package:expense_splitter_web_app/src/domain/entities/user.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/user_repository.dart';
import 'package:flutter/material.dart';
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class RegisterController extends Controller {
  RegisterController(
    UserRepository userRepository,
  ) : userRepository = userRepository;

  UserRepository userRepository;

  User? user;

  String username = '';
  String emailLogin = '';
  String passwordLogin = '';
  String email = '';
  String password = '';
  String passwordAgain = '';
  bool termsAndPrivacyAccepted = false;

  bool isLoading = false;
  bool? isLoginValid;
  bool? isEmailValid;
  bool isRegisterValid = false;
  bool? isUsernameAvaliable;
  bool? isPasswordsMatch;

  String? verifiedCode;

  @override
  void initListeners() {}

  void setEmailLogin(String value) {
    emailLogin = value;
    isLoginValid = null;
    refreshUI();
  }

  void setPasswordLogin(String value) {
    passwordLogin = value;
    isLoginValid = null;
    refreshUI();
  }

  void setUsername(String value) {
    isUsernameAvaliable = null;
    username = value;
    refreshUI();
  }

  void setEmail(String value) {
    isEmailValid = null;
    email = value;
    refreshUI();
  }

  void setPassword(String value) {
    isPasswordsMatch = null;
    password = value;
    refreshUI();
  }

  void setPasswordAgain(String value) {
    isPasswordsMatch = null;
    passwordAgain = value;
    refreshUI();
  }

  bool isFieldsAreInitializedForLogin() {
    return emailLogin != '' && passwordLogin != '';
  }

  bool isFieldsAreInitializedForRegister() {
    return email != '' && password != '' && username != '' && passwordAgain != '' && termsAndPrivacyAccepted;
  }

  void toggleTermsAndPolicy() {
    termsAndPrivacyAccepted = !termsAndPrivacyAccepted;
    refreshUI();
  }

  void logIn(BuildContext context) async {
    isLoginValid = null;
    isLoading = true;
    refreshUI();
    try {
      await userRepository.logIn(emailLogin, passwordLogin);
    } catch (e) {
      if (e is InvalidLoginException) {
        isLoginValid = false;
      }
    }

    if (isLoginValid != false) {
      WebNavigator.navigateToDashboardView(context);
    }
    isLoading = false;
    refreshUI();
  }

  void signUp(BuildContext context) async {
    isLoading = true;
    refreshUI();

    if (password != passwordAgain) {
      isRegisterValid = false;
      isPasswordsMatch = false;
      isLoading = false;
      refreshUI();
      return;
    }

    user = User(
      id: '',
      username: username,
      email: email,
      password: sha256.convert(utf8.encode(password)).toString(),
    );
    try {
      await userRepository.signUp(user!);
      WebNavigator.navigateToDashboardView(context);
      refreshUI();
    } catch (e, st) {
      print(e);
      print(st);
      rethrow;
    }
    isLoading = false;
    refreshUI();
  }
}

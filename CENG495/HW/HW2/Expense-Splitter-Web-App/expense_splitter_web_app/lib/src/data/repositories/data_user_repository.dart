import 'dart:convert';

import 'package:crypto/crypto.dart';
import 'package:dio/dio.dart';
import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/data/exceptions/invalid_login_exception.dart';
import 'package:expense_splitter_web_app/src/domain/entities/user.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/user_repository.dart';

class DataUserRepository implements UserRepository {
  static final _instance = DataUserRepository._internal();
  DataUserRepository._internal();
  factory DataUserRepository() => _instance;

  static User? user;
  final dio = Dio();
  String port = "5000";

  @override
  Future<void> signUp(User newUser) async {
    try {
      var response = await dio.request(
        '$endpoint:$port/register',
        options: Options(
          method: 'POST',
          headers: headers,
        ),
        data: newUser.toJson(),
      );

      if (response.statusCode == 201) {
        user = newUser.copyWith();
        print(json.encode(response.data));
      } else {
        print(response.statusMessage);
      }
    } catch (e, st) {
      print(e);
      print(st);
      rethrow;
    }
  }

  @override
  Future<void> logIn(String email, String password) async {
    try {
      String hashedPassword = sha256.convert(utf8.encode(password)).toString();
      var response = await dio.request(
        '$endpoint:$port/login',
        options: Options(
          method: 'POST',
          headers: headers,
        ),
        data: {
          "email": email,
          "password": hashedPassword,
        },
      );

      print(response.statusCode);
      if (response.statusCode == 200) {
        user = User.fromJson(response.data["user"]);
        print('User logged in successfully.');
      }
    } catch (e, st) {
      print(e);
      print(st);
      throw InvalidLoginException();
    }
  }

  @override
  Future<bool?> getIfEmailAvaliableForRegister() async {
    throw UnimplementedError();
  }

  @override
  User? getCurrentUser() {
    return user;
  }

  @override
  void logOut() {
    user = null;
    print('User logged out successfully.');
  }
}

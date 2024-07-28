import 'package:expense_splitter_web_app/src/domain/entities/user.dart';

abstract class UserRepository {
  Future<void> signUp(User user);
  Future<void> logIn(String email, String password);
  Future<bool?> getIfEmailAvaliableForRegister();
  User? getCurrentUser();
  void logOut();
}

import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:expense_splitter_web_app/src/app/pages/register/register_view.dart';
import 'package:flutter/material.dart';

class App extends StatelessWidget {
  const App({super.key});
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "Expense Splitter",
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        scaffoldBackgroundColor: kBackgroundColor,
        colorScheme: ColorScheme.fromSeed(seedColor: kPrimaryColor),
        useMaterial3: true,
        fontFamily: 'Poppins',
      ),
      home: Scaffold(
        body: RegisterView(),
      ),
    );
  }
}

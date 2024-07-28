import 'package:flutter/material.dart';

final kFadeInDuration = Duration(milliseconds: 365);

const kPrimaryColor = Color(0xFFD2202F);
Color kPrimaryColorPale = kPrimaryColor.withOpacity(0.6);
Color kPrimaryColorHint = kPrimaryColor.withOpacity(0.5);

const kBlack = Colors.black;
Color kBlackPale = kBlack.withOpacity(0.7);
Color kBlackHint = kBlack.withOpacity(0.5);

const kWhite = Colors.white;
const kBorderColor = Color(0xffD8DADC);
const kBackgroundColor = Color(0xffF8F8F8);

final kDeactiveColor = Color(0xff000000).withOpacity(0.25);

final String endpoint = "http://localhost";

var headers = {
  'Content-Type': 'application/json',
};

TextStyle kTitleStyle({Color? color}) {
  return TextStyle(
    color: color ?? kBlack,
    fontSize: 30,
    fontWeight: FontWeight.w700,
    fontFamily: 'Poppins',
  );
}

TextStyle kSubtitleStyle({Color? color}) {
  return TextStyle(
    color: color ?? kBlackPale,
    fontSize: 16,
    fontWeight: FontWeight.w400,
  );
}

TextStyle kAppBarTitleStyle() {
  return TextStyle(
    color: kBlack,
    fontSize: 18,
    fontWeight: FontWeight.w600,
    fontFamily: 'Poppins',
  );
}

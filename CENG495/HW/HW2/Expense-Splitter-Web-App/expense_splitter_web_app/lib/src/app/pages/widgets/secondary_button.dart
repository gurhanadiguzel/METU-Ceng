import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class SecondaryButton extends StatelessWidget {
  final String text;
  final Function()? onPressed;
  final bool isEnabled;
  final bool isLoading;

  SecondaryButton({
    required this.text,
    required this.onPressed,
    required this.isEnabled,
    required this.isLoading,
  });

  @override
  Widget build(BuildContext context) {
    return AnimatedContainer(
      duration: Duration(milliseconds: 200),
      decoration: BoxDecoration(
        color: isEnabled ? kPrimaryColor : kPrimaryColorHint,
        borderRadius: BorderRadius.circular(10),
      ),
      child: TextButton(
        child: Container(
          alignment: Alignment.center,
          child: isLoading
              ? CircularProgressIndicator(
                  color: kWhite,
                )
              : Text(
                  text,
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontSize: 18,
                    fontFamily: 'Inter',
                    color: kWhite,
                  ),
                ),
        ),
        onPressed: () {
          if (isEnabled) {
            onPressed!();
            HapticFeedback.lightImpact();
          }
        },
      ),
    );
  }
}

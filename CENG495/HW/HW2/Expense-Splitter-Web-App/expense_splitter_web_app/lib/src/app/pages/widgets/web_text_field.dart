import 'package:expense_splitter_web_app/src/app/constants.dart';
import 'package:flutter/material.dart';

class WebTextField extends StatelessWidget {
  const WebTextField({
    super.key,
    required this.size,
    required this.title,
    required this.hintText,
    required this.isObscure,
    required this.onChanged,
    this.color,
    this.initialValue,
  });

  final Size size;
  final String title;
  final String hintText;
  final bool isObscure;
  final void Function(String text) onChanged;
  final Color? color;
  final String? initialValue;

  @override
  Widget build(BuildContext context) {
    return Container(
      width: (size.width - 40) / 2,
      child: Column(
        children: [
          Container(
            width: (size.width - 40) / 2,
            child: Text(
              title,
              textAlign: TextAlign.left,
              style: TextStyle(
                fontSize: 14,
                fontWeight: FontWeight.w400,
              ),
            ),
          ),
          SizedBox(height: 6),
          TextFormField(
            style: TextStyle(height: 1),
            obscureText: isObscure,
            decoration: InputDecoration(
              enabledBorder: OutlineInputBorder(
                borderSide: BorderSide(color: color ?? kBorderColor),
                borderRadius: BorderRadius.circular(10),
              ),
              filled: false,
              hintStyle: TextStyle(color: kBlackHint),
              hintText: hintText,
            ),
            onChanged: onChanged,
            initialValue: initialValue,
          ),
        ],
      ),
    );
  }
}

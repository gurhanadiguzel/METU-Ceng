import 'package:flutter/material.dart';

class WebAppBar extends StatelessWidget {
  const WebAppBar({
    Key? key,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    Size size = MediaQuery.of(context).size;
    return SingleChildScrollView(
      child: Container(
        color: Colors.white,
        width: size.width, // Adjust width based on screen size
        height: size.height * 0.2,
        padding: EdgeInsets.symmetric(horizontal: size.width * 0.05),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            SizedBox(
              width: 60,
              height: 60,
            ),
            Container(
              width: 350,
              child: ClipRRect(
                borderRadius: BorderRadius.circular(50),
                child: Text(
                  "Expense Splitter",
                  style: TextStyle(
                    fontSize: 36,
                    fontWeight: FontWeight.w600,
                  ),
                ),
              ),
            ),
            Container(
              width: 60,
              child: ClipRRect(
                borderRadius: BorderRadius.circular(size.width * 0.01), // 1% of the screen width
                child: Image.network(
                  'https://raw.githubusercontent.com/gurhanadiguzel/Flutter-Projects/main/images/ceng.png',
                  fit: BoxFit.cover,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

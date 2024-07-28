import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/expense.dart';
import 'package:expense_splitter_web_app/src/domain/entities/participant.dart';
import 'package:expense_splitter_web_app/src/domain/entities/user.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/user_repository.dart';
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class EventDetailsController extends Controller {
  EventDetailsController(
    UserRepository userRepository,
    this.event,
  ) : _userRepository = userRepository;

  final UserRepository _userRepository;
  final Event event;

  User? currentUser;

  @override
  void initListeners() {}

  @override
  void onInitState() {
    currentUser = _userRepository.getCurrentUser();
    super.onInitState();
  }

  double getTotalExpensesAmount(Event event) {
    double total = 0;
    for (Expense expense in event.expenses) {
      total += expense.amount;
    }
    return total;
  }

  double getTotalPaidAmountForUsername(Event event, String username) {
    double total = 0;
    for (Expense expense in event.expenses) {
      if (expense.payer.name == username) total += expense.amount;
    }
    return total;
  }

  double calculateCostPerUser(Event event) {
    double total = getTotalExpensesAmount(event);
    return total / event.participants.length;
  }

  double calculateDebtForUser(Event event, String username) {
    double total = getTotalPaidAmountForUsername(event, username) - calculateCostPerUser(event);
    return total;
  }

  List<String> getAllDebts() {
    List<double> debts = [];
    List<String> result = [];
    for (Participant participant in event.participants) {
      debts.add(calculateDebtForUser(event, participant.name));
    }

    for (int i = 0; i < debts.length; i++) {
      if (debts[i] < 0) {
        for (int j = 0; j < debts.length; j++) {
          if (debts[j] > 0) {
            if (debts[i].abs() <= debts[j]) {
              result.add(
                  '${event.participants[i].name} gives ${debts[i].abs().toStringAsFixed(2)} TL to ${event.participants[j].name}');
              debts[j] -= debts[i].abs();
              debts[i] = 0;
              break;
            } else {
              result.add(
                  '${event.participants[i].name} gives ${debts[j].toStringAsFixed(2)} TL to ${event.participants[j].name}');
              debts[i] += debts[j].abs();
              debts[j] = 0;
            }
          }
          if (debts[i] == 0) {
            break;
          }
        }
      }
    }
    return result;
  }
}

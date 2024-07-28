import 'package:expense_splitter_web_app/src/domain/entities/event.dart';
import 'package:expense_splitter_web_app/src/domain/entities/participant.dart';
import 'package:expense_splitter_web_app/src/domain/entities/user.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/event_repository.dart';
import 'package:expense_splitter_web_app/src/domain/repositories/user_repository.dart';
import 'package:flutter_clean_architecture/flutter_clean_architecture.dart';

class AddEventController extends Controller {
  AddEventController(
    EventRepository eventRepository,
    UserRepository userRepository,
  )   : _eventRepository = eventRepository,
        userRepository = userRepository;

  final EventRepository _eventRepository;
  final UserRepository userRepository;

  User? user;
  String? eventName;
  List<Participant> participants = [];
  List<bool?> isParticipantsSetted = [null];
  bool? isEventNameSetted;
  bool? isNavigateEnable;

  @override
  void initListeners() {}
  @override
  void onInitState() {
    user = userRepository.getCurrentUser()!.copyWith();
    participants.add(Participant(name: user!.username));
    super.onInitState();
  }

  void addEvent() async {
    Event event = Event(
      id: '',
      eventName: eventName!,
      participants: participants,
      date: DateTime.now(),
      createdByEmail: user!.email,
      expenses: [],
    );

    await _eventRepository.addEvent(event);
  }

  void addParticipant() {
    participants.add(Participant(name: ''));
    isParticipantsSetted.add(null);
    refreshUI();
  }

  void setEventName(String? input) {
    isNavigateEnable = null;
    eventName = input;
    isEventNameSetted = true;
    refreshUI();
  }

  void setParticipantName(String value, int index) {
    isNavigateEnable = null;
    participants[index].name = value;
    isParticipantsSetted[index] = true;
    refreshUI();
  }

  void checkNavigateEnable() {
    if (eventName == null || eventName == '') {
      isEventNameSetted = false;
      isNavigateEnable = false;
    }
    for (int i = 0; i < participants.length; i++) {
      if (participants[i].name == '') {
        isParticipantsSetted[i] = false;
        isNavigateEnable = false;
      }
    }
    if (isNavigateEnable != false) isNavigateEnable = true;

    refreshUI();
  }
}

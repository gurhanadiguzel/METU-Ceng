class Participant {
  String name;

  Participant({
    required this.name,
  });

  Map<String, dynamic> toJson() => {
        'name': name,
      };

  factory Participant.fromJson(Map<String, dynamic> json) => Participant(
        name: json['name'],
      );

  Participant copyWith({
    String? name,
  }) =>
      Participant(
        name: name ?? this.name,
      );
}

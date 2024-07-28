class User {
  final String id;
  final String username;
  final String email;
  String password;

  User({
    required this.id,
    required this.username,
    required this.email,
    required this.password,
  });

  factory User.fromJson(Map<String, dynamic> json) {
    return User(
      id: json['_id'],
      email: json['email'],
      password: json['password'],
      username: json['username'],
    );
  }

  Map<String, dynamic> toJson() {
    return {
      if (id != '') '_id': {"\$oid": id},
      'email': email,
      'password': password,
      'username': username,
    };
  }

  User copyWith({
    String? id,
    String? email,
    String? password,
    String? username,
  }) {
    return User(
      id: id ?? this.id,
      email: email ?? this.email,
      password: password ?? this.password,
      username: username ?? this.username,
    );
  }
}

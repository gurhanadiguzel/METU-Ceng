from flask import Flask, request , jsonify
from pymongo import MongoClient 
from bson.json_util import dumps
from bson import ObjectId
from flask_cors import CORS

app = Flask(__name__) 
CORS(app)

# Set up MongoDB connection and collection 
client = MongoClient(host ='host.docker.internal',port = 27017) 
db = client['expense_splitter'] 
collection = db['users'] 

@app.route('/') 
def ping_server(): 
    return 'Welcome to Expense Splitter!'

# Add data to MongoDB route 
@app.route('/register', methods=['POST']) 
def register_user():  
    data = request.json
    email = data.get('email')
    password = data.get('password')
    username = data.get('username')

    if email and password and username:
        # Insert data into MongoDB 
        collection.insert_one(data) 
        return jsonify({'message': 'User registered successfully'}), 201
    else:
        return jsonify({'error': 'Missing required fields'}), 400
    
    
@app.route('/login', methods=['POST']) 
def login():  
    data = request.json
    email = data.get('email')
    password = data.get('password')

    if email and password:
        # Query the database to find the user with the provided email
        user = collection.find_one({"email": email})

        # Check if the user exists and if the password matches
        if user and user['password'] == password:
            # Return the user data without the password and the access token
            user_data = {
                '_id': str(user['_id']),
                'email': user['email'],
                'password': user['password'],
                'username': user['username'],
            }
            return jsonify({'user': user_data}), 200
        else:
            return jsonify({'message': 'Invalid email or password'}), 401
    else:
        return jsonify({'message': 'Email and password are required'}), 400
    
@app.route('/get_user') 
def get_user(): 
    # Get data from MongoDB 
    user = collection.find_one({"email": "grhnadgzl@example.com"})
    if user:
        return str(user['_id']) 
    else:
        return 'User not found'

if __name__ == '__main__': 
    app.run(host="0.0.0.0", port=5000, debug=True)
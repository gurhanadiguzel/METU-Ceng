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
collection = db['events'] 

@app.route('/') 
def ping_server(): 
    return 'Welcome to Expense Splitter!'

@app.route('/add_event', methods=['POST']) 
def add_event():  
    data = request.json
    # Insert data into MongoDB 
    collection.insert_one(data) 
    return jsonify({'message': 'Evet has been added successfully'}), 201

@app.route('/get_events', methods=['GET']) 
def get_events():  
    email = request.args.get('email')
    if email:
        # Find events in MongoDB based on the provided email
        events = collection.find({"createdByEmail": email})
        # Return events as JSON response
        return dumps({'events': events}), 200
    else:
        return jsonify({'message': 'Email parameter is missing'}), 400
    
@app.route('/add_expense', methods=['POST']) 
def add_expense():  
    data = request.json
    eventId = data.get('eventId')
    expense = data.get('expense')
    
    event = collection.find_one({"_id": ObjectId(eventId)})

    if event:
        # Append the new expense to the event's expenses list
        event['expenses'].append(expense)
        
        # Update the event in the database with the new expense
        collection.update_one({"_id": ObjectId(eventId)}, {"$set": event})

        return jsonify({'message': 'Expense has been added to the event successfully'}), 201
    else:
        return jsonify({'error': 'Event not found'}), 404



if __name__ == '__main__': 
    app.run(host="0.0.0.0", port=5050, debug=True)
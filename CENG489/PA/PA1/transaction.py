import threading
import requests
import datetime
import json
import jwt
import hashlib
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.backends import default_backend
import time

base_url = "https://gradecoin.yigitsever.com"

def get_transactions():
    try:
        response = requests.get(base_url + "/transaction")
        if response.status_code == 200:
            #print("Transactions retrieved successfully:", response.json())
            return  response.json()

        else:
            print("Error: Failed to retrieve transactions. Status code:", response.status_code)
    except requests.exceptions.RequestException as e:
        print("Error: Failed to retrieve transactions:", e)


def send_transaction(source, target, amount, timestamp, private_key): 
    transaction_json = {
        "source": source,
        "target": target,
        "amount": amount,
        "timestamp": timestamp,
    }

    serialized_transaction = json.dumps(transaction_json, separators=(",", ":"))
    transaction_hash = hashlib.md5(serialized_transaction.encode()).hexdigest()

    timestamp_datetime = datetime.datetime.fromisoformat(timestamp)
    unix_timestamp = timestamp_datetime.timestamp()

    iat = int(unix_timestamp)
    exp = iat + 3600  

    payload = {
        "tha": transaction_hash,
        "iat": iat,
        "exp": exp  
    }

    jwt_token = jwt.encode(payload, private_key, algorithm="RS256")

    headers = {
        "Authorization": "Bearer " + jwt_token
    }

    try:
        response = requests.post(base_url + "/transaction", json=transaction_json, headers=headers)
        if response.status_code == 201:
            print("Transaction sent successfully:", response.json())
        else:
            print("Error: Failed to send transaction. Status code:", response.status_code, response.text)
    except requests.exceptions.RequestException as e:
        print("Error: Failed to send transaction:", e)

def compute_hash(transaction_list, nonce, timestamp):
    block_content = {
        "transaction_list": transaction_list,
        "nonce": nonce,
        "timestamp": timestamp
    }
    serialized_block = json.dumps(block_content, separators=(",", ":"))
    return hashlib.blake2s(serialized_block.encode()).hexdigest()

# Helper function to mine a valid block
# def mine_block(transaction_list, hash_zeros, timestamp):
#     nonce = 0
#     prefix = '0' * hash_zeros
#     while True:
#         hash_value = compute_hash(transaction_list, nonce, timestamp)
#         if hash_value.startswith(prefix):
#             return nonce, hash_value
#         nonce += 1

def mine_block(transaction_list, hash_zeros, timestamp, start_nonce, step, result):
    nonce = start_nonce
    prefix = '0' * hash_zeros
    while not result.get('found'):
        hash_value = compute_hash(transaction_list, nonce, timestamp)
        if hash_value.startswith(prefix):
            result['found'] = True
            result['nonce'] = nonce
            result['hash'] = hash_value
            break
        nonce += step

def mine_block_with_threads(transaction_list, hash_zeros, timestamp, thread_count=10):
    result = {'found': False, 'nonce': None, 'hash': None}
    threads = []
    for i in range(thread_count):
        thread = threading.Thread(target=mine_block, args=(transaction_list, hash_zeros, timestamp, i, thread_count, result))
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()

    return result['nonce'], result['hash']

def send_block(private_key, transaction_list, timestamp):
    print('Start writing block')
    response = requests.get(base_url + "/config")
    config = response.json()
    hash_zeros = config["hash_zeros"]

    nonce, block_hash = mine_block_with_threads(transaction_list, hash_zeros, timestamp)

    block = {
        "transaction_list": transaction_list,
        "nonce": nonce,
        "timestamp": timestamp,
        "hash": block_hash
    }

    timestamp_datetime = datetime.datetime.fromisoformat(timestamp)
    unix_timestamp = timestamp_datetime.timestamp()

    iat = int(unix_timestamp)
    exp = iat + 3600 

    payload = {
        "tha": block_hash,
        "iat": iat,
        "exp": exp   
    }

    jwt_token = jwt.encode(payload, private_key, algorithm="RS256")

    headers = {
        "Authorization": "Bearer " + jwt_token
    }

    try:
        response = requests.post(base_url + "/block", json=block, headers=headers)
        if response.status_code == 201:
            print("Block sent successfully:", response.json())
        else:
            print("Error: Failed to send block. Status code:", response.status_code, response.text)
    except requests.exceptions.RequestException as e:
        print("Error: Failed to send block:", e)

if __name__ == "__main__":
    source = open('fingerprint.txt','r').read()
    target1 = "e1d2703567bfb0fe4547128461b51cd1cf205f3a545fb96f057655940c1d0eee" 
    target2 = "ea11afb7665e255a6bd10b0a8823153aba17aadc156b30e64749a47e9468b0a7"
    target3 = "f267ba915f0cc01f1d78a63083fcaa4f41a0b7fcb1bc85baaaeb2c83cc22340c"
    target4 = "917bb3f5c2c366aba31e32f81b11b5f2a821ddecc6e6664c816f8c88a0187193"
    target5 = "a3071b03f6ecb3df9145a1ac0ae3196bc9bb7e6b851c5c92f9cca0774772611d"
    target6 = "a5233b869b5dc89b830e7a99941b4719d404ecf001828ce2ca196cd74529c668"
    amount = 1
    timestamp = datetime.datetime.now().replace(microsecond=0).isoformat()

    with open('private_key.pem', 'rb') as f:
        private_key = f.read()

    fingerprint = open('fingerprint.txt', 'r').read().strip()

    while True:
        send_transaction(source, target1, amount, timestamp, private_key)
        time.sleep(1)
        send_transaction(source, target2, amount, timestamp, private_key)
        time.sleep(1)
        send_transaction(source, target3, amount, timestamp, private_key)
        time.sleep(1)
        send_transaction(source, target4, amount, timestamp, private_key)
        time.sleep(1)
        send_transaction(source, target5, amount, timestamp, private_key)
        time.sleep(1)
        send_transaction(source, target6, amount, timestamp, private_key)

        transactions_json = get_transactions()

        transactions = list(transactions_json.values())
        transaction_list = list(transactions_json.keys())

        while len(transaction_list) < 10:
            transactions_json = get_transactions()
            transactions = list(transactions_json.values())
            transaction_list = list(transactions_json.keys())
            print('slepping')
            time.sleep(10)

        for index in range(len(transactions)):
            if transactions[index].get('source') == fingerprint:
                transaction_list[0], transaction_list[index] = transaction_list[index], transaction_list[0]
                break

        nonce = 0
        timestamp = datetime.datetime.now().replace(microsecond=0).isoformat()

        with open('private_key.pem', 'rb') as f:
            private_key = f.read()

        send_block(private_key, transaction_list, timestamp)

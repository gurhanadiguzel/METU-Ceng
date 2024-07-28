import datetime
import hashlib
import json
import threading
import jwt
import requests

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

def get_blocks():
    try:
        response = requests.get(base_url + "/block")
        if response.status_code == 200:
            print("Blocks retrieved successfully:", response.json())
            return response.json()
        else:
            print("Error: Failed to retrieve blocks. Status code:", response.status_code)
    except requests.exceptions.RequestException as e:
        print("Error: Failed to retrieve blocks:", e)

def compute_hash(transaction_list, nonce, timestamp):
    block_content = {
        "transaction_list": transaction_list,
        "nonce": nonce,
        "timestamp": timestamp
    }
    serialized_block = json.dumps(block_content, separators=(",", ":"))
    return hashlib.blake2s(serialized_block.encode()).hexdigest()

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
    fingerprint = open('fingerprint.txt', 'r').read().strip()
    transactions_json = get_transactions()

    # Convert the transactions_json dictionary to a list of transactions (dicts)
    transactions = list(transactions_json.values())
    transaction_list = list(transactions_json.keys())

    # Reorder transactions such that the first transaction with a matching source is at the front
    for index in range(len(transactions)):
        if transactions[index].get('source') == fingerprint:
            transaction_list[0], transaction_list[index] = transaction_list[index], transaction_list[0]
            break

    nonce = 0
    timestamp = datetime.datetime.now().replace(microsecond=0).isoformat()

    with open('private_key.pem', 'rb') as f:
        private_key = f.read()

    send_block(private_key, transaction_list, timestamp)
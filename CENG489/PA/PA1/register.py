from cryptography.hazmat.primitives import serialization, hashes, padding
from cryptography.hazmat.primitives.asymmetric import padding as asymmetric_padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import base64
import json
import os
import requests

def generate_temp_key():
    temp_key = os.urandom(16)  # 16 bytes = 128 bits
    return temp_key

def generate_iv():
    iv = os.urandom(16)  # 16 bytes = 128 bits
    return iv

def encrypt_data(serialized_data, key, iv):
    # Initialize the AES cipher with CBC mode and PKCS7 padding
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()

    # Pad the serialized data
    padder = padding.PKCS7(algorithms.AES.block_size).padder()
    padded_data = padder.update(serialized_data.encode()) + padder.finalize()

    # Encrypt the padded data
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()

    # Encode the encrypted data with Base64
    return base64.b64encode(encrypted_data).decode()

def register_to_gradecoin():
    serialized_P_AR = json.dumps({
        "student_id": student_id,
        "passwd": password,
        "public_key": public_key
    })

    k_temp = generate_temp_key()

    iv = generate_iv()

    # Encrypt the serialized data
    C_AR = encrypt_data(serialized_P_AR, k_temp, iv)

    # Encrypt the temporary key using RSA with OAEP padding scheme and SHA-256 hashing
    gradecoin_public_key_obj = serialization.load_pem_public_key(
        gradecoin_public_key.encode(),
        backend=default_backend()
    )
    
    key_ciphertext = gradecoin_public_key_obj.encrypt(
        k_temp,
        asymmetric_padding.OAEP(
            mgf=asymmetric_padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    key_ciphertext_b64 = base64.b64encode(key_ciphertext).decode()

    # Encode the IV with Base64
    iv_b64 = base64.b64encode(iv).decode()

    # Create the payload JSON object
    auth_request = {
        "c": C_AR,
        "iv": iv_b64,
        "key": key_ciphertext_b64
    }

    return auth_request
def send_register_request(auth_request):
    registration_url = "https://gradecoin.yigitsever.com/register"

    try:
        response = requests.post(registration_url, json=auth_request)
        
        if response.status_code == 201:
            print("Registration successful!")
            print("Response from server:", response.json())
        else:
            print("Registration failed. Status code:", response.status_code)
            print("Response from server:", response.text)
    
    except Exception as e:
        print("An error occurred while sending the registration request:", e)


if __name__ == "__main__":
    student_id = "e244802"
    password = "imGbe39r0qlVDs0yy5Xlt0MKuS7eX9yQ"

    with open("gradecoin.pub", "r") as file:
        gradecoin_public_key = file.read()
    print(gradecoin_public_key)

    with open("public_key.pem", "r") as file:
        public_key = file.read()
    print(public_key)


    auth_request = register_to_gradecoin()
    print("Auth Request:", auth_request)

    send_register_request(auth_request)
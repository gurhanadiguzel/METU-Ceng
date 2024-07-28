import requests

base_url = "https://gradecoin.yigitsever.com"

def get_version():  
    try:
        response = requests.get(base_url + "/version")  
        print("Version retrieved successfully:", response.text)
    except requests.exceptions.RequestException as e:
        print("Error: Failed to retrieve version:", e)

def get_config():
    try:
        response = requests.get(base_url + "/config")
        if response.status_code == 200:
            print("Configs retrieved successfully:", response.json())
    except requests.exceptions.RequestException as e:
        print("Error: Failed to retrieve configs:", e)


get_config()
#get_version()
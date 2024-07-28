import requests

def register_course(course_code, session_token):
    url = "https://serbetcibasi.com/register"
    payload = {"course": course_code}
    headers = {"session": session_token}
    
    try:
        response = requests.post(url, data=payload, headers=headers)
        if response.status_code == 200:
            print(response.text)
            print("Course registration successful!")
        else:
            print("Failed to register for the course. Status code:", response.status_code)
    except requests.RequestException as e:
        print("Error:", e)

# Example usage:
course_code = "CENG111"  # Replace "CENGXXX" with the actual course code
session_token = "eyJ1c2VybmFtZSI6ImUyNDQ4MDIifQ.Zlrzbw.LAswgFi6E3mCdtR5cXvHEjWOoHI"
register_course(course_code, session_token)

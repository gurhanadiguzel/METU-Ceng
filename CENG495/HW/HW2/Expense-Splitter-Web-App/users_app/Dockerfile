FROM python:3.9-slim-buster AS users-container

WORKDIR /app

COPY requirements.txt requirements.txt

RUN pip3 install -r requirements.txt

COPY app_users.py .

CMD ["python3", "app_users.py"]


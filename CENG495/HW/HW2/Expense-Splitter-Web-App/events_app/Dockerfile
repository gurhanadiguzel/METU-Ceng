FROM python:3.9-slim-buster AS events-container

WORKDIR /app

COPY requirements.txt requirements.txt

RUN pip3 install -r requirements.txt

COPY app_events.py .

CMD ["python3", "app_events.py"]



# FROM python:3.9-slim-buster

# WORKDIR /app

# COPY requirements.txt requirements.txt

# RUN pip3 install -r requirements.txt

# COPY . .

# CMD [ "python3", "app.py"]

# Honeypot Project Report

## Introduction
This report documents the Honeypot Project, dedicated to simulating a dynamic network environment in an attack scenario.

## Environment Setup

### Flask
#### What is Flask?
Flask is a lightweight and flexible web framework for Python, known for its simplicity and modularity.

#### Why do we use Flask in this project?
Flask serves as the backbone of the backend infrastructure for the Honeypot Project. Here's why Flask is chosen:
- **Ease of Development:** Flask offers a straightforward and intuitive development experience.
- **Modularity:** Flask promotes a modular design, facilitating scalability and maintainability.
- **Containerization:** Flask applications can be containerized using Docker, providing isolation and reproducibility.
- **Dynamic Behavior:** Flask files implement dynamic behavior to respond to events within the Honeypot environment.

#### Implementing Dynamic Port Switching in Flask
Each Flask application running on different ports facilitates dynamic port switching in response to attacks.

### Docker
#### Introduction to Docker
Docker is a popular containerization platform, ideal for simplifying the development, testing, and deployment processes.

#### Project Overview
In the Honeypot Project, Docker is utilized to containerize a multi-component application composed of several Flask microservices.

#### Communication Flow
The communication between containers is orchestrated using Flask, starting from the gateway container.

#### Encountered Challenges and Solutions
- **Networking Challenges Post-Containerization:** Initially, Flask applications were configured to run on localhost, which failed in Docker's isolated network environment. We resolved this by using host.docker.internal.
- **Deployment Issues with Kubernetes:** Locally deploying Docker containers on Kubernetes posed challenges, which we addressed by uploading containers to Docker Hub.

#### Conclusions and Recommendations
The transition to a fully containerized environment using Docker presented initial challenges, but strategic solutions were implemented to streamline the deployment process.

### Kubernetes
#### Introduction to Kubernetes
Kubernetes is used for container orchestration, optimizing the deployment and management of application components.

#### Project Overview
Configuration tasks were broken down into two YAML files: one for deployment specifics and the other for service definitions.

#### Deployment Methodology
'kubectl create' commands were used to integrate configurations into the Kubernetes environment, simplifying deployment and improving reliability.

## Screenshots
Insert screenshots here.

## Conclusion
The Honeypot Project aims to create a resilient and adaptive network environment. The integration of Flask, Kubernetes, Minikube, and Docker enabled the creation of a robust system capable of responding to dynamic security challenges.

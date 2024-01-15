#  <img src="https://github.com/Nouhaila-Akhziz/SmartHome/assets/114859285/3ec9ea1b-5795-49cc-af49-008d63bb91c1" alt="in_pairs Logo" style="width:3%;"> SmartHome 

A Smart Home Project represents the integration of advanced technologies to create an intelligent and automated living space. This innovative endeavor involves the incorporation of various devices and systems that can be controlled and monitored remotely, enhancing convenience, comfort, and efficiency for inhabitants. Typically, a Smart Home includes interconnected devices such as smart lighting, thermostats, security cameras, door locks, and more, all accessible through a centralized control interface, often a smartphone app or voice commands.

The core idea is to create an environment where everyday tasks are automated, responding to user preferences, schedules, and environmental conditions. For instance, smart thermostats adjust temperature settings based on occupancy and personal preferences, while smart lighting systems can be programmed to adapt to different moods or scenarios. Security is bolstered with intelligent surveillance and access control, providing real-time alerts and remote monitoring.

A Smart Home Project often involves a combination of sensors, actuators, and a central hub to enable seamless communication and coordination among devices. This interconnected ecosystem not only offers convenience but also promotes energy efficiency and enhances home security. The continual evolution of smart home technologies ensures that residents can enjoy a more streamlined, connected, and intelligent living experience.

## Hardware Part:

### 1. Door System with RFID:
Our Door System utilizes an RFID card for opening. The RFID sensor detects the card and transmits the information to the servo motor, which activates the door opening. This simple yet crucial principle enhances the security of our home.

### 2. room:
In the bedroom, we've integrated a DHT11 sensor measuring temperature and humidity. This sensor works by measuring resistance variations due to temperature and humidity. The values are visualized in our PC console, providing precise control over the indoor environment.

### 3. Presence Sensor (PIR) with LED:
To optimize energy usage, we've integrated a PIR presence sensor that lights up an LED when a person is detected. This contributes to more efficient resource utilization and automation based on presence.

### 4. Gas Detector with LED and Buzzer:
Our system is equipped with an MQ2 gas detector, which, upon detection, activates a red LED for visual warning and a buzzer for audible alerts. These actions are crucial for user safety against gas-related incidents.

### 5. Automatic Fan in Gas Leak:
Finally, to ensure maximum safety, our system automatically activates a fan in case of a gas leak. This helps eliminate potential dangers by quickly evacuating the gas.

## Software Part:
<p float="left">
  <img src="https://github.com/Nouhaila-Akhziz/SmartHome/assets/114859285/3e2dcd70-b850-44b1-ac38-2e76cb945e69" width="45%" />
  <img src="https://github.com/Nouhaila-Akhziz/SmartHome/assets/114859285/02097088-b59c-4997-a9e7-2883ef3eea5b" width="45%" />
  
</p>
We have created a website, and you can find more details on our GitHub repository: [SmartHome GitHub Repository](https://github.com/Nouhaila-Akhziz/SmartHome)

## Link between Hardware and Software:

We use the MQTT protocol, and a Raspberry Pi serves as the central hub, ensuring seamless communication between the hardware components and the software, providing a robust and efficient Smart Home system.


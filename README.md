# Drowsiness-Detecting-Vehicle

[![Language](https://img.shields.io/badge/Language-Python-yellow.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/Programming_language)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg?style=for-the-badge)](https://github.com/YOUR_USERNAME/drowsiness-detecting-vehicle/graphs/commit-activity)

This project implements a driver drowsiness detection system designed to enhance road safety. Using computer vision and facial landmark analysis, the system identifies signs of driver fatigue and can trigger alerts to help prevent accidents.

---

## 📑 Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

---

## ✅ Features

- Real-time drowsiness detection using facial landmarks.
- Eye and facial movement analysis with OpenCV and dlib.
- Hardware integration possible using NodeMCU (see `nodemcu_code/`).
- Alert mechanism possibly supported via Blynk platform (`blynk_test.py`).
- Optional visualization and hardware layout with included circuit and PCB PDFs.

---

## 🛠 Technologies Used

- **Language:** Python
- **Libraries & Tools:**
  - `OpenCV`
  - `dlib`
  - `imutils`
  - `Blynk` (for hardware alerts)
  - `shape_predictor_68_face_landmarks.dat` (Dlib landmark model)
  - Microcontroller code in C++ for NodeMCU

---

## ⚙️ Installation

Follow these steps to set up the project locally:

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/drowsiness-detecting-vehicle.git
cd drowsiness-detecting-vehicle
```

### 2. Install Dependencies

Ensure Python (3.6 or above) and pip are installed. Then run:

```bash
pip install -r requirements.txt
```

> Note: You may need to install additional system packages depending on your OS, especially for `dlib`.

### 3. Prepare the Dlib Model

This project requires `shape_predictor_68_face_landmarks.dat`. If only a `.bz2` version is included:

```bash
bzip2 -d shape_predictor_68_face_landmarks.dat.bz2
```

Place the resulting `.dat` file in the project root.

---

## 🚀 Usage

### Run the Drowsiness Detection System

```bash
python driver_drowsiness.py
```

This launches the camera feed and analyzes facial landmarks in real time.

### Optional Hardware Integration

- Configure and upload code from `nodemcu_code/` to your ESP8266/NodeMCU.
- If using Blynk for notifications, make sure to set your Blynk credentials in `blynk_test.py`.

---

## 📁 Project Structure

```
.
├── Circuit_diagram.pdf                          # Schematic for hardware alert system
├── PCB.pdf                                      # PCB layout (if hardware implemented)
├── blynk_test.py                                # Test script for Blynk platform alerts
├── driver_drowsiness.py                         # Main application script
├── face_recognition/                            # Additional facial analysis code (if any)
├── nodemcu_code/                                # Embedded C++ code for NodeMCU hardware
├── requirements.txt                             # Python package dependencies
├── shape_predictor_68_face_landmarks.dat        # Required dlib model (after extraction)
├── shape_predictor_68_face_landmarks.dat.bz2    # Compressed version of model
└── README.md
```

---

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch  
   ```bash
   git checkout -b feature/YourFeature
   ```
3. Commit your changes  
   ```bash
   git commit -m "Add YourFeature"
   ```
4. Push your branch  
   ```bash
   git push origin feature/YourFeature
   ```
5. Open a pull request and describe your changes

---

## License

Distributed under the MIT License. See [LICENSE](https://github.com/Dixon1323/smart-hydrophonics-system/blob/main/LICENSE.md) for more information.

---

## 🙏 Acknowledgements

- [Dlib Face Detection](http://dlib.net/)
- [OpenCV Library](https://opencv.org/)
- [Blynk IoT Platform](https://blynk.io/)
- Communities on Stack Overflow, GitHub, and various YouTube tutorials for guidance.

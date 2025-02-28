# Botler - Robot de Catering
## Guía y documentación

Este proyecto presenta el diseño para el manejo de un robot diferencial con la capacidad de operar en un entorno cerrado en relación en la industria del servicio (catering), el robot es capaz de:

- Mapear: mediante el sensor RPlidar A1, se utilizó el algoritmo de localización y mapeo simultáneo (SLAM) hector mapping para así generar un mapa 2D del entorno de trabajo.

- Navegar: mediante el algoritmo AMCL y DWAPlanner se logró la planeación y navegación de nuestro robot en el entorno previamente mapeado.

La arquitectura del robot se basa en la comunicación entre 2 micro controladores, el microcontrolador P2 Edge es el encargado del funcionamiento de los motores Hub mediante la recepción de valores de velocidad enviados por el ESP32, el microcoontrolador ESP32 permite la interación con ROS para la realización de mapeo por TeleOp o navegación en el entorno cerrado.

Referencia del diagrama de conexiones para el funcionamiento del robot.

![image](https://github.com/user-attachments/assets/10fb5bba-ee98-44d1-9b0a-e2b8ebb918dd)

### Librería para el control de motores HUB
El funcionamiento y control de los motores HUB fue gracias a la librería [ironsheep](https://github.com/ironsheep), se adjunta el link del repisotorio con toda la información con respecto a la librería: [P2-BLDC-Motor-Control](https://github.com/ironsheep/P2-BLDC-Motor-Control).

> Se recomienda descargar la carpeta /src y colocar el código "Control_MotoresHun" en la misma carpeta

El archivo isp_bldc_motor_userconfig.spin2 es el encargado de la configuración de los drivers para el motor, de acuerdo a las características del motor, pines utilizados y tipo de bateria. Se utilizó esta configuración para el control de ambos motores.
    
    MOTOR_TYPE = MOTR_6_5_INCH

    LEFT_MOTOR_BASE = PINS_P0_P15
    RIGHT_MOTOR_BASE = PINS_P16_P31

    DRIVE_VOLTAGE = PWR_25p9V

    WHEEL_DIA_IN_INCH = 6.5   ' 6.5 inches (floating point constant)

    LEFT_BOARD_TYPE = BRD_AUTO_DET
    RIGHT_BOARD_TYPE = BRD_AUTO_DET
La configuración se realiza en esta sección
![image](https://github.com/user-attachments/assets/1b1d9324-8801-496c-af04-74388578f606)

Con las configuraciones respectivas se trabaja en el código main para la recepción de datos y control de los motores hub.





    

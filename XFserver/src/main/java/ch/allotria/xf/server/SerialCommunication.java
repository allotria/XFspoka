package ch.allotria.xf.server;

import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;

public class SerialCommunication {

    private static SerialCommunication _instance = null;
    private SerialPort serialPort;

    private SerialCommunication() {
        // singleton
        initPort();
    }

    private void initPort() {

        String defaultPort = getDefaultPort();

        Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            CommPortIdentifier portId = (CommPortIdentifier) portList
                    .nextElement();

            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {

                if (portId.getName().equals(defaultPort)) {
                    try {
                        serialPort = (SerialPort) portId.open("XFserver", 2000);
                    } catch (PortInUseException e) {
                        // TODO logging
                    }
                }
            }
        }
    }

    private String getDefaultPort() {
        // TODO read serial port from properties file
        return null;
    }

    public static SerialCommunication getInstance() {
        if (_instance == null) {
            _instance = new SerialCommunication();
        }

        return _instance;
    }
}

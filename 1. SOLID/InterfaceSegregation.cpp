/*
* File: InterfaceSegregation.cpp
* Author: trung.la
* Date: 08-03-2025
* Description: This file is the implementation of Interface Segregation Principle
*/

#include <iostream>
#include <string>
#include <vector>

// ==========================================
// WITHOUT INTERFACE SEGREGATION PRINCIPLE
// ==========================================

/**
 * @brief DeviceInterface class
 * This class defines the interface for a device.
 * A "fat" interface that handle multiple responsibilities.
 */

class DeviceInterface
{
public:
    virtual ~DeviceInterface() = default;

    virtual void print(const std::string &document) = 0;
    virtual void scan(const std::string &document) = 0;
    virtual void fax(const std::string &document) = 0;
    virtual void copy(const std::string &document) = 0;
};

class MultiPrinter : public DeviceInterface
{
public:
    void print(const std::string &document) override {
        std::cout << "Printing: " << document << std::endl;
    }

    void scan(const std::string &document) override {
        // Not supported
    }

    void fax(const std::string &document) override {
        // Not supported
    }

    void copy(const std::string &document) override {
        // Not supported
    }
};

class BasicPrinter : public DeviceInterface
{
public:
    void print(const std::string &document) override {
        std::cout << "Printing: " << document << std::endl;
    }

    void scan(const std::string &document) override {
        std::cout << "Scanning: " << document << std::endl;
    }

    void fax(const std::string &document) override {
        // Not supported
        throw std::runtime_error("Fax not supported");
    }

    void copy(const std::string &document) override {
        // Not supported
        throw std::runtime_error("Copy not supported");
    }
};

// Demonstrate code without ISP
void demonstrateWithoutISP() {

    std::string document = "Document";
    MultiPrinter multiPrinter;
    multiPrinter.print(document);
    multiPrinter.scan(document);
    multiPrinter.fax(document);
    multiPrinter.copy(document);

    BasicPrinter basicPrinter;
    basicPrinter.print(document);
    basicPrinter.scan(document);
    try {
        basicPrinter.fax(document);
    } catch (const std::runtime_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        basicPrinter.copy(document);
    } catch (const std::runtime_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    /* The MultiPrinter class implements all the methods of the DeviceInterface
     * but does not support scanning, faxing, or copying. The BasicPrinter class
     * implements all the methods of the DeviceInterface but does not support faxing
     * or copying. This violates the Interface Segregation Principle because the
     * classes are forced to implement methods that they do not need.
     */
}


// ==========================================
// WITH INTERFACE SEGREGATION PRINCIPLE
// ==========================================

/**
 * @brief IPrinter interface
 * This interface defines the print method for a printer.
 */
class IPrinter
{
public:
    virtual ~IPrinter() = default;
    virtual void print(const std::string &document) = 0;
};

/**
 * @brief IScanner interface
 * This interface defines the scan method for a scanner.
 */
class IScanner
{
public:
    virtual ~IScanner() = default;
    virtual void scan(const std::string &document) = 0;
};

/**
 * @brief IFax interface
 * This interface defines the fax method for a fax machine.
 */
class IFax
{
public:
    virtual ~IFax() = default;
    virtual void fax(const std::string &document) = 0;
};

/**
 * @brief ICopy interface
 * This interface defines the copy method for a copier.
 */
class ICopy
{
public:
    virtual ~ICopy() = default;
    virtual void copy(const std::string &document) = 0;
};

/**
 * @brief Printer class
 * This class implements the IPrinter interface for a printer.
 */
class Printer : public IPrinter
{
public:
    void print(const std::string &document) override {
        std::cout << "Printing: " << document << std::endl;
    }
};

/**
 * @brief Scanner class
 * This class implements the IScanner interface for a scanner.
 */
class Scanner : public IScanner
{
public:
    void scan(const std::string &document) override {
        std::cout << "Scanning: " << document << std::endl;
    }
};

/**
 * @brief Fax class
 * This class implements the IFax interface for a fax machine.
 */
class Fax : public IFax
{
public:
    void fax(const std::string &document) override {
        std::cout << "Faxing: " << document << std::endl;
    }
};

/**
 * @brief Copier class
 * This class implements the ICopy interface for a copier.
 */
class Copier : public ICopy
{
public:
    void copy(const std::string &document) override {
        std::cout << "Copying: " << document << std::endl;
    }
};

/**
 * @brief MultiFunctionDevice class
 * This class implements all the interfaces for a multi-function device.
 */
class MultiFunctionDevice : public IPrinter, public IScanner, public IFax, public ICopy
{
public:
    void print(const std::string &document) override {
        std::cout << "Printing: " << document << std::endl;
    }

    void scan(const std::string &document) override {
        std::cout << "Scanning: " << document << std::endl;
    }

    void fax(const std::string &document) override {
        std::cout << "Faxing: " << document << std::endl;
    }

    void copy(const std::string &document) override {
        std::cout << "Copying: " << document << std::endl;
    }
};

/**
 * @brief BasicFunctionDevice class
 * This class implements only the IPrinter and IScanner interfaces for a basic device.
 * It does not support faxing or copying.
 */

class BasicFunctionDevice : public IPrinter, public IScanner
{
public:
    void print(const std::string &document) override {
        std::cout << "Printing: " << document << std::endl;
    }

    void scan(const std::string &document) override {
        std::cout << "Scanning: " << document << std::endl;
    }
};

// Demonstrate code with ISP
void demonstrateWithISP() {

    std::string document = "Document";
    Printer printer;
    printer.print(document);

    Scanner scanner;
    scanner.scan(document);

    Fax fax;
    fax.fax(document);

    Copier copier;
    copier.copy(document);

    MultiFunctionDevice multiFunctionDevice;
    multiFunctionDevice.print(document);
    multiFunctionDevice.scan(document);
    multiFunctionDevice.fax(document);
    multiFunctionDevice.copy(document);

    BasicFunctionDevice basicFunctionDevice;
    basicFunctionDevice.print(document);
    basicFunctionDevice.scan(document);

    /* The Printer class implements the IPrinter interface, the Scanner class
     * implements the IScanner interface, the Fax class implements the IFax interface,
     * and the Copier class implements the ICopy interface. The MultiFunctionDevice
     * class implements all the interfaces for a multi-function device, and the
     * BasicFunctionDevice class implements only the IPrinter and IScanner interfaces
     * for a basic device. This adheres to the Interface Segregation Principle because
     * each class implements only the methods that it needs.
     */
}

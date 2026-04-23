#include <iostream>
#include <string>
using namespace std;

// Base Component Interface
class IDataSource {
public:
    virtual void writeData(const string& data) const = 0;
    virtual void readData() const = 0;
    virtual ~IDataSource() = default;
};

// Concrete Component
class FileDataSource : public IDataSource {
private:
    string fileName;
public:
    FileDataSource(const string& name) : fileName(name) {}
    void writeData(const string& data) const override {
        cout << "[FileDataSource] Writing to file '" << fileName << "': " << data << endl;
    }
    void readData() const override {
        cout << "[FileDataSource] Reading data from file '" << fileName << "'..." << endl;
    }
};

// Base Decorator
class DataSourceDecorator : public IDataSource {
protected:
    IDataSource* wrappedDataSource;
public:
    DataSourceDecorator(IDataSource* source) : wrappedDataSource(source) {}
    void writeData(const string& data) const override {
        wrappedDataSource->writeData(data);
    }
    void readData() const override {
        wrappedDataSource->readData();
    }
};

// Concrete Decorator - Encryption
class EncryptionDecorator : public DataSourceDecorator {
public:
    EncryptionDecorator(IDataSource* source) : DataSourceDecorator(source) {}
    void writeData(const string& data) const override {
        string encryptedData = "[Encrypted]" + data; // Simulate encryption
        cout << "[EncryptionDecorator] Encrypting data..." << endl;
        wrappedDataSource->writeData(encryptedData);
    }
    void readData() const override {
        cout << "[EncryptionDecorator] Decrypting data..." << endl;
        wrappedDataSource->readData();
    }
};

// Concrete Decorator - Compression
class CompressionDecorator : public DataSourceDecorator {
public:
    CompressionDecorator(IDataSource* source) : DataSourceDecorator(source) {}
    void writeData(const string& data) const override {
        string compressedData = "[Compressed]" + data; // Simulate compression
        cout << "[CompressionDecorator] Compressing data..." << endl;
        wrappedDataSource->writeData(compressedData);
    }
    void readData() const override {
        cout << "[CompressionDecorator] Decompressing data..." << endl;
        wrappedDataSource->readData();
    }
};

// Client function
void processData(IDataSource* dataSource) {
    dataSource->writeData("Hello World");
    dataSource->readData();
}

int main() {
    // Basic file data source
    FileDataSource* fileSource = new FileDataSource("data.txt");

    //cout << "--- Writing/Reading without decorators ---" << endl;
    //processData(fileSource);

    //cout << "\n--- Writing/Reading with Encryption ---" << endl;
    EncryptionDecorator* encryptedSource = new EncryptionDecorator(fileSource);
    //processData(encryptedSource);

    cout << "\n--- Writing/Reading with Compression and Encryption ---" << endl;
    CompressionDecorator* compressedEncryptedSource = new CompressionDecorator(encryptedSource);
    processData(compressedEncryptedSource);

    delete compressedEncryptedSource; // will not delete inner automatically
    delete encryptedSource;
    delete fileSource;

    return 0;
}

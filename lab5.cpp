#include <iostream>
#include <string>
#include <vector>

using namespace std;

class File {
protected:
    string fileName;
    string extension;
    int size;
    string creationDate;
    string attributes;

public:
    File(string name, string ext, int sz, string date, string attr) : fileName(name), extension(ext), size(sz), creationDate(date), attributes(attr) {}

    string getFileName() const {
        return fileName;
    }

    string getExtension() const {
        return extension;
    }

    int getSize() const {
        return size;
    }

    string getCreationDate() const {
        return creationDate;
    }

    string getAttributes() const {
        return attributes;
    }

    void setFileName(string name) {
        fileName = name;
    }

    void setExtension(string ext) {
        extension = ext;
    }

    void setSize(int sz) {
        size = sz;
    }

    void setCreationDate(string date) {
        creationDate = date;
    }

    void setAttributes(string attr) {
        attributes = attr;
    }

    virtual void display() const {
        cout << "File Name: " << fileName << endl;
        cout << "Extension: " << extension << endl;
        cout << "Size: " << size << " bytes" << endl;
        cout << "Creation Date: " << creationDate << endl;
        cout << "Attributes: " << attributes << endl;
    }
};

class SpecializedFile : public File {
private:
    string additionalField1;
    string additionalField2;

public:
    SpecializedFile(string name, string ext, int sz, string date, string attr, string field1, string field2) : File(name, ext, sz, date, attr), additionalField1(field1), additionalField2(field2) {}

    string getAdditionalField1() const {
        return additionalField1;
    }

    string getAdditionalField2() const {
        return additionalField2;
    }

    void setAdditionalField1(string field1) {
        additionalField1 = field1;
    }

    void setAdditionalField2(string field2) {
        additionalField2 = field2;
    }

    void display() const override {
        File::display();
        cout << "Additional Field 1: " << additionalField1 << endl;
        cout << "Additional Field 2: " << additionalField2 << endl;
    }
};

int main() {
    vector<File*> database;

    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Add a new file\n";
        cout << "2. Edit an existing file\n";
        cout << "3. Delete an existing file\n";
        cout << "4. Display all files\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, ext, date, attr, field1, field2;
            int size;
            cout << "Enter file name: ";
            cin >> name;
            cout << "Enter extension: ";
            cin >> ext;
            cout << "Enter size (in bytes): ";
            cin >> size;
            cout << "Enter creation date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter attributes: ";
            cin >> attr;
            cout << "Enter additional field 1: ";
            cin >> field1;
            cout << "Enter additional field 2: ";
            cin >> field2;
            File* newFile = new SpecializedFile(name, ext, size, date, attr, field1, field2);
            database.push_back(newFile);
            cout << "File added successfully.\n";
            break;
        }
        case 2: {
            string name;
            cout << "Enter the name of the file to edit: ";
            cin >> name;
            // Find the file in the database and edit it
            for (File* file : database) {
                if (file->getFileName() == name) {
                    string newName, newExt, newDate, newAttr, newField1, newField2;
                    int newSize;
                    cout << "Enter new file name: ";
                    cin >> newName;
                    cout << "Enter new extension: ";
                    cin >> newExt;
                    cout << "Enter new size (in bytes): ";
                    cin >> newSize;
                    cout << "Enter new creation date (YYYY-MM-DD): ";
                    cin >> newDate;
                    cout << "Enter new attributes: ";
                    cin >> newAttr;
                    cout << "Enter new additional field 1: ";
                    cin >> newField1;
                    cout << "Enter new additional field 2: ";
                    cin >> newField2;
                    // Update file information
                    file->setFileName(newName);
                    file->setExtension(newExt);
                    file->setSize(newSize);
                    file->setCreationDate(newDate);
                    file->setAttributes(newAttr);
                    if (SpecializedFile* specializedFile = dynamic_cast<SpecializedFile*>(file)) {
                        specializedFile->setAdditionalField1(newField1);
                        specializedFile->setAdditionalField2(newField2);
                    }
                    cout << "File edited successfully.\n";
                    break;
                }
            }
            break;
        }
        case 3: {
            string name;
            cout << "Enter the name of the file to delete: ";
            cin >> name;
            // Find the file in the database and delete it
            for (auto it = database.begin(); it != database.end(); ++it) {
                if ((*it)->getFileName() == name) {
                    delete* it;
                    database.erase(it);
                    cout << "File deleted successfully.\n";
                    break;
                }
            }
            break;
        }
        case 4: {
            // Display all files
            for (File* file : database) {
                file->display();
                cout << endl;
            }
            break;
        }
        case 0: {
            cout << "Exiting...\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
        }
    } while (choice != 0);

    // Clean up dynamic memory
    for (File* file : database) {
        delete file;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <limits>

// ������
class Task {
public:
    std::string name;
    std::string description;
    int progress; // �i�ס]�ʤ���^
    std::string responsiblePerson; // �t�d�H
    std::string lastEditor; // �̫�s���

    Task(const std::string& name, const std::string& description, int progress, const std::string& responsiblePerson, const std::string& lastEditor)
        : name(name), description(description), progress(progress), responsiblePerson(responsiblePerson), lastEditor(lastEditor) {}

    // �C�L���ȸԲӫH��
    void printDetails() const {
        std::cout << "���ȦW��: " << name << std::endl;
        std::cout << "�y�z: " << description << std::endl;
        std::cout << "�i��: " << progress << "%" << std::endl;
        std::cout << "�t�d�H: " << responsiblePerson << std::endl;
        std::cout << "�̫�s���: " << lastEditor << std::endl;
    }
};

// �ζ�������
class TeamMember {
protected:
    std::string name;
    std::vector<Task> tasks; // �����t�d������

public:
    TeamMember(const std::string& name) : name(name) {}

    // �K�[����
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    // ��s�M�׶i��
    void updateTaskProgress(const std::string& updater) {
        std::string taskName;
        int newProgress = 0; // ��l�Ƭ� 0

        std::cout << "�п�J�n��s���M�צW��: ";
        std::getline(std::cin, taskName);

        // �ھڱM�צW�٬d��M�׶i��
        int originalProgress = findTaskProgress(taskName);

        if (originalProgress == -1) {
            std::cout << "�S�����W�� '" << taskName << "' ���M�סC" << std::endl;
        }
        else {
            std::cout << "��M�׶i��: " << originalProgress << "%" << std::endl;
            newProgress = validateProgressInput();

            // ��s�M�׶i��
            for (Task& task : tasks) {
                if (task.name == taskName) {
                    task.progress = newProgress;
                    task.lastEditor = updater;
                    break;
                }
            }
            std::cout << "�M�׶i�פw��s�C" << std::endl;
        }
    }

    // �d�߯S�w�H���t�d���Ҧ��M��List��T
    void printProjectsByMember(const std::string& memberName) const {
        std::cout << "�����m�W: " << name << std::endl;
        std::cout << "�t�d���Ҧ��M��:" << std::endl;
        for (const Task& task : tasks) {
            if (task.responsiblePerson == memberName) {
                task.printDetails();
                std::cout << std::endl;
            }
        }
    }

    // �R���S�w�M��
    void deleteProject(const std::string& projectName) {
        auto it = tasks.begin();
        while (it != tasks.end()) {
            if (it->name == projectName) {
                it = tasks.erase(it);
                std::cout << "�M�פw�R���C" << std::endl;
                return;
            }
            else {
                ++it;
            }
        }
        std::cout << "�S�����W�� '" << projectName << "' ���M�סC" << std::endl;
    }

private:
    // ���ұM�׶i�׿�J
    int validateProgressInput() const {
        int newProgress;
        std::cout << "�п�J��s���M�׶i��(0-100)�έ�]: ";
        std::cin >> newProgress;

        // ���ҿ�J�O�_�b���Ľd��
        while (newProgress < 0 || newProgress > 100 || std::cin.fail()) {
            std::cout << "��J�L�ġI�п�J0-100�������Ʀr: ";
            std::cin.clear(); // �M�����~�лx
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������~��J
            std::cin >> newProgress;
        }

        std::cin.ignore(); // �M���e���� \n

        return newProgress;
    }

    int findTaskProgress(const std::string& taskName) const {
        int originalProgress = -1;
        for (const Task& task : tasks) {
            if (task.name == taskName) {
                originalProgress = task.progress;
                break;
            }
        }
        return originalProgress;
    }
};

// ���ұM�׶i�׿�J
int validateProgressInput() {
    int newProgress;
    std::cout << "�п�J��s���M�׶i��(0-100)�έ�]: ";
    std::cin >> newProgress;

    // ���ҿ�J�O�_�b���Ľd��
    while (newProgress < 0 || newProgress > 100 || std::cin.fail()) {
        std::cout << "��J�L�ġI�п�J0-100�������Ʀr: ";
        std::cin.clear(); // �M�����~�лx
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������~��J
        std::cin >> newProgress;
    }

    std::cin.ignore(); // �M���e���� \n

    return newProgress;
}

int main() {
    std::string userName;
    std::cout << "�п�J�z���m�W: ";
    std::getline(std::cin, userName);

    TeamMember member(userName);

    int choice;
    bool continueOperation = true;

    while (continueOperation) {
        std::cout << "�п�ܭn�i�檺�ާ@�G" << std::endl;
        std::cout << "1. �إ߷s�M�׶i��" << std::endl;
        std::cout << "2. ��s�M�׶i��" << std::endl;
        std::cout << "3. �R���M��" << std::endl;
        std::cout << "4. �d�߯S�w�H���t�d���Ҧ��M��List��T" << std::endl;
        std::cout << "5. ���}" << std::endl;
        std::cin >> choice;

        std::cin.ignore(); // �M���e���� \n

        if (choice == 1) {
            std::string projectName, projectDescription, responsiblePerson;
            int projectProgress;

            std::cout << "�п�J�M�צW�ٻP�y�z�]�榡�G�W�� �y�z�^: ";
            std::getline(std::cin, projectName);
            std::getline(std::cin, projectDescription);
            std::cout << "�п�J�M�׶i��(0-100): ";
            std::cin >> projectProgress;

            // ���ҿ�J�O�_�b���Ľd��
            projectProgress = validateProgressInput();

            std::cout << "�п�J�t�d�H�m�W: ";
            std::cin.ignore(); // �M���e���� \n
            std::getline(std::cin, responsiblePerson);

            member.addTask(Task(projectName, projectDescription, projectProgress, responsiblePerson, userName));
        }
        else if (choice == 2) {
            member.updateTaskProgress(userName);
        }
        else if (choice == 3) {
            std::string projectName;
            std::cout << "�п�J�n�R�����M�צW��: ";
            std::getline(std::cin, projectName);
            member.deleteProject(projectName);
        }
        else if (choice == 4) {
            std::string memberName;
            std::cout << "�п�J�n�d�ߪ������m�W: ";
            std::getline(std::cin, memberName);

            member.printProjectsByMember(memberName);
        }
        else if (choice == 5) {
            continueOperation = false;
        }
        else {
            std::cout << "�L�Ī��ﶵ�I" << std::endl;
        }
    }

    return 0;
}
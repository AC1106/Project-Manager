#include <iostream>
#include <vector>
#include <string>
#include <limits>

// 任務類
class Task {
public:
    std::string name;
    std::string description;
    int progress; // 進度（百分比）
    std::string responsiblePerson; // 負責人
    std::string lastEditor; // 最後編輯者

    Task(const std::string& name, const std::string& description, int progress, const std::string& responsiblePerson, const std::string& lastEditor)
        : name(name), description(description), progress(progress), responsiblePerson(responsiblePerson), lastEditor(lastEditor) {}

    // 列印任務詳細信息
    void printDetails() const {
        std::cout << "任務名稱: " << name << std::endl;
        std::cout << "描述: " << description << std::endl;
        std::cout << "進度: " << progress << "%" << std::endl;
        std::cout << "負責人: " << responsiblePerson << std::endl;
        std::cout << "最後編輯者: " << lastEditor << std::endl;
    }
};

// 團隊成員類
class TeamMember {
protected:
    std::string name;
    std::vector<Task> tasks; // 成員負責的任務

public:
    TeamMember(const std::string& name) : name(name) {}

    // 添加任務
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    // 更新專案進度
    void updateTaskProgress(const std::string& updater) {
        std::string taskName;
        int newProgress = 0; // 初始化為 0

        std::cout << "請輸入要更新的專案名稱: ";
        std::getline(std::cin, taskName);

        // 根據專案名稱查找專案進度
        int originalProgress = findTaskProgress(taskName);

        if (originalProgress == -1) {
            std::cout << "沒有找到名為 '" << taskName << "' 的專案。" << std::endl;
        }
        else {
            std::cout << "原專案進度: " << originalProgress << "%" << std::endl;
            newProgress = validateProgressInput();

            // 更新專案進度
            for (Task& task : tasks) {
                if (task.name == taskName) {
                    task.progress = newProgress;
                    task.lastEditor = updater;
                    break;
                }
            }
            std::cout << "專案進度已更新。" << std::endl;
        }
    }

    // 查詢特定人員負責的所有專案List資訊
    void printProjectsByMember(const std::string& memberName) const {
        std::cout << "成員姓名: " << name << std::endl;
        std::cout << "負責的所有專案:" << std::endl;
        for (const Task& task : tasks) {
            if (task.responsiblePerson == memberName) {
                task.printDetails();
                std::cout << std::endl;
            }
        }
    }

    // 刪除特定專案
    void deleteProject(const std::string& projectName) {
        auto it = tasks.begin();
        while (it != tasks.end()) {
            if (it->name == projectName) {
                it = tasks.erase(it);
                std::cout << "專案已刪除。" << std::endl;
                return;
            }
            else {
                ++it;
            }
        }
        std::cout << "沒有找到名為 '" << projectName << "' 的專案。" << std::endl;
    }

private:
    // 驗證專案進度輸入
    int validateProgressInput() const {
        int newProgress;
        std::cout << "請輸入更新的專案進度(0-100)或原因: ";
        std::cin >> newProgress;

        // 驗證輸入是否在有效範圍內
        while (newProgress < 0 || newProgress > 100 || std::cin.fail()) {
            std::cout << "輸入無效！請輸入0-100之間的數字: ";
            std::cin.clear(); // 清除錯誤標誌
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略錯誤輸入
            std::cin >> newProgress;
        }

        std::cin.ignore(); // 清除前面的 \n

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

// 驗證專案進度輸入
int validateProgressInput() {
    int newProgress;
    std::cout << "請輸入更新的專案進度(0-100)或原因: ";
    std::cin >> newProgress;

    // 驗證輸入是否在有效範圍內
    while (newProgress < 0 || newProgress > 100 || std::cin.fail()) {
        std::cout << "輸入無效！請輸入0-100之間的數字: ";
        std::cin.clear(); // 清除錯誤標誌
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略錯誤輸入
        std::cin >> newProgress;
    }

    std::cin.ignore(); // 清除前面的 \n

    return newProgress;
}

int main() {
    std::string userName;
    std::cout << "請輸入您的姓名: ";
    std::getline(std::cin, userName);

    TeamMember member(userName);

    int choice;
    bool continueOperation = true;

    while (continueOperation) {
        std::cout << "請選擇要進行的操作：" << std::endl;
        std::cout << "1. 建立新專案進度" << std::endl;
        std::cout << "2. 更新專案進度" << std::endl;
        std::cout << "3. 刪除專案" << std::endl;
        std::cout << "4. 查詢特定人員負責的所有專案List資訊" << std::endl;
        std::cout << "5. 離開" << std::endl;
        std::cin >> choice;

        std::cin.ignore(); // 清除前面的 \n

        if (choice == 1) {
            std::string projectName, projectDescription, responsiblePerson;
            int projectProgress;

            std::cout << "請輸入專案名稱與描述（格式：名稱 描述）: ";
            std::getline(std::cin, projectName);
            std::getline(std::cin, projectDescription);
            std::cout << "請輸入專案進度(0-100): ";
            std::cin >> projectProgress;

            // 驗證輸入是否在有效範圍內
            projectProgress = validateProgressInput();

            std::cout << "請輸入負責人姓名: ";
            std::cin.ignore(); // 清除前面的 \n
            std::getline(std::cin, responsiblePerson);

            member.addTask(Task(projectName, projectDescription, projectProgress, responsiblePerson, userName));
        }
        else if (choice == 2) {
            member.updateTaskProgress(userName);
        }
        else if (choice == 3) {
            std::string projectName;
            std::cout << "請輸入要刪除的專案名稱: ";
            std::getline(std::cin, projectName);
            member.deleteProject(projectName);
        }
        else if (choice == 4) {
            std::string memberName;
            std::cout << "請輸入要查詢的成員姓名: ";
            std::getline(std::cin, memberName);

            member.printProjectsByMember(memberName);
        }
        else if (choice == 5) {
            continueOperation = false;
        }
        else {
            std::cout << "無效的選項！" << std::endl;
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define RECORD_SIZE sizeof(struct Employee)

struct Employee {
    int id;
    char name[30];
    float salary;
};

void create_and_write(const char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    struct Employee employees[3] = {
        {101, "Ravi Kumar", 45000.0},
        {102, "Anita Sharma", 52000.0},
        {103, "Vikram Singh", 39000.0}
    };

    for (int i = 0; i < 3; i++) {
        write(fd, &employees[i], RECORD_SIZE);
    }

    close(fd);
    printf("File created and 3 employee records written\n");
}

void update_record(const char *filename, int record_num, float new_salary) {
    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    struct Employee emp;
    off_t offset = (record_num - 1) * RECORD_SIZE;

    lseek(fd, offset, SEEK_SET);
    read(fd, &emp, RECORD_SIZE);

    emp.salary = new_salary;

    lseek(fd, offset, SEEK_SET);
    write(fd, &emp, RECORD_SIZE);

    close(fd);
    printf("Record %d updated with new salary %.2f\n", record_num, new_salary);
}

void read_record(const char *filename, int record_num) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    struct Employee emp;
    off_t offset = (record_num - 1) * RECORD_SIZE;

    lseek(fd, offset, SEEK_SET);
    read(fd, &emp, RECORD_SIZE);

    printf("Record %d -> ID: %d, Name: %s, Salary: %.2f\n",
           record_num, emp.id, emp.name, emp.salary);

    close(fd);
}

int main() {
    const char *filename = "employees.dat";

    create_and_write(filename);
    read_record(filename, 2);
    update_record(filename, 2, 60000.0);
    read_record(filename, 2);
    read_record(filename, 1);
    read_record(filename, 3);

    return 0;
}
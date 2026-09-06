#ifndef PARSER_H_
#define PARSER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_COMMANDS  16
#define MAX_ARGV      16
#define MAX_HIST      8



typedef enum {single, first, middle, last, unknown} position_codes;



// Структура cmd команды.
typedef struct cmd_t
{
  char* argv[MAX_ARGV];           // Массив аргументов.
  position_codes pos;             // Позиция в конвейере (одиночная, первая, средняя или последняя).
} cmd_t;



// Структура истории команд cmd.
typedef struct cmd_hist
{
  char* history[MAX_HIST];        // История команд.
  size_t oldest_cmd_idx;          // Индекс самой старой команды.
  size_t count;                   // Количество эл-ов в истории.
}cmd_hist;



/**
 * @brief               Удаляет запись из истории по индексу.
 * 
 * @param cmd_history   структура истории cmd команд.
 * @param cmd_idx       индекс записи истории, которую необходимо удалить.
 */
void remove_history_entry(cmd_hist* cmd_history, size_t cmd_idx);



/**
 * @brief               Добавление новой записи в историю.
 * 
 * @param cmd_history   указатель на структуру истории.
 * @param cmd           строка, содержащая команды, которю необходимо добавить в историю.
 */
void add_history_entry(cmd_hist* cmd_history, char* cmd);



/**
 * @brief               По индексу получает команду из истории.
 * 
 * @param cmd_history   структура истории cmd команд.
 * @param entry_idx     индекс записи из истории, которую нужно получить.
 * @return              Команда, извлечённая из истории. Если в истории нет записей, то возвращается NULL.
 */
char* get_history_entry(cmd_hist* cmd_history, size_t entry_idx);



/**
 * @brief               Проверяет состоит ли строка из одних пробелов.
 * 
 * @param str           проверяемая строка.
 * @return true         - строка состоит только из пробелов;
 * @return false        - строка состоит не только из пробелов.
 */
bool empty(char* str);



/**
 * @brief               Удаляет пробелы из начала строки.
 * 
 * @param str           преобразуемая строка.
 * @return              Исходная строка, из начала которой удалены пробелы.
 */
char* ltrim(char* str);



/**
 * @brief               Удаляет пробелы из начала строки.
 * 
 * @param str           преобразуемая строка.
 * @return              Исходная строка, из начала которой удалены пробелы.
 */
char* rtrim(char* str);



/**
 * @brief               Удаляет пробелы из начала и конца строки.
 * 
 * @param str           преобразуемая строка.
 * @return              Исходная строка, из начала и конца которой удалены пробелы.
 */
char* trim(char* str);



/**
 * @brief               Разбивает исходную строку со всеми командами на отдельные подкоманды и каждую подкоманду кладёт в массив.
 *                      Подкоманды отделены друг от друга символом-разделителем. В исходной строке символ-разделитель заменяется на '\0'.
 * 
 * @param str           исходная строка с командами.
 * @param delimiter     символ-разделитель.
 * @param cmds          массив, в который будут складываться разделённые команды.
 */
void parse_cmds(char* str, const char* delimiter, char* cmds[]);



/**
 * @brief               Определяет какую позицию занимает команда в терминале.
 * 
 * @param cmd_index     индекс команды, позицию которой нужно узнать.
 * @param cmds_amount   количество введённых в терминал команд.
 * @return              Код позции, на которой стоит рассматриваемая команда.
 */
position_codes cmd_position(size_t cmd_index, size_t cmds_amount);



/**
 * @brief               Делит исходную строку на команды и производит начальную инициализацию (заполняет массив аргументов) каждой команды.
 * 
 * @param str           исходная строка команд.
 * @param cmds_array    массив команд.
 * @return              Количество прочитанных команд.
 */
size_t first_pass(char *str, cmd_t* cmds_array);



/**
 * @brief               Производит финальную инициализацию (заполняет поле кода позции) каждой команды и добавляет их в историю.
 * 
 * @param cmds_array    массив команд.
 * @param cmds_amount   количество команд в массиве.
 */
void second_pass(cmd_t* cmds_array, size_t cmds_amount);



/**
 * @brief               Разбивает исходную строку на команды, инициализирует их и добаляет в историю.
 * 
 * @param str           исходная строка команд.
 * @param cmds_array    массив команд.
 * @param history       структура истории cmd команд.
 * @return              Количество прочитанных команд.
 */
int parse_commands(char *str, cmd_t* cmds_array, cmd_hist* history);



/**
 * @brief               (debug) Преобразует код позиции команды в строку.
 * 
 * @param pos           код позиции команды.
 * @return              Строка, соответствующая позиции команды.
 */
char* position_to_string(position_codes pos);



/**
 * @brief               (debug) Печатает аргументы из массива.
 * 
 * @param argv          массив аргументов.
 */
void print_argv(char* argv[]);



/**
 * @brief               (debug) Печатает информацию (позицию, список аргументов) о командах из массива.
 * 
 * @param cmds_array    массив команд.
 * @param cmds_amount   количество команд в массиве команд.
 */
void print_commands(cmd_t* cmds_array, size_t cmds_amount);



/**
 * @brief               (debug) Печатает историю.
 * 
 * @param cmd_history   структура истории.
 */
void print_history(const cmd_hist* cmd_history);



#endif // PARSER_H_
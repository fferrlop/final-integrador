#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

    struct ColorConsole {
        static constexpr auto fg_blue = "\033[34m";
        static constexpr auto bg_white = "\033[47m";
    };

    struct ConsoleBox {
        void new_text() {/*...*/}
        void set_text(const string &text) { cout << text << endl; }
    };

ConsoleBox *consoleBox = new ConsoleBox;

    void load_script(const char* filename, bool show_script = false) {
        string script;
        FILE *file = nullptr;

        try {
            file = fopen(filename, "r");
            if (!file) {
                throw runtime_error("No se pudo abrir el archivo.");
            }

            char buf[4001];
            size_t bytes_read = fread(buf, 1, 4000, file);
            while (bytes_read > 0) {
                buf[bytes_read] = '\0';
                script.append(buf);
                bytes_read = fread(buf, 1, 4000, file);
            }

            fclose(file);
            file = nullptr;

            if (show_script) {
                cout << ColorConsole::fg_blue << ColorConsole::bg_white;
                cout << script << endl;
            }
            consoleBox->new_text();
            consoleBox->set_text(script);
        }

        catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
            if (file) {
                fclose(file);
            }
        }
    }

int main() {
    load_script();
    return 0;
}

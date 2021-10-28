#include <iostream>
#include <string>
enum types {
TEXT_FIELD = 1,
RADIO_BTN = 2,
CHECK_BOX = 4,
COMBO_BOX = 8,
MOUSE_LISTENERS = 16};
using namespace std;

//NP = NoParams
string newJObjectNP(string type, string varName) {
    string ret = varName + " = new " + type + "();\n";
    return ret;
}

string newJObject(string type, string sufix, string varName) {
    string ret = sufix + varName + " = new " + type + "(\"" + varName + "\");\n";
    return ret;
}

string newLbl(string varName) {
    string ret = "JLabel lbl" + varName + " = new JLabel" + "(\"" + varName + "\");\n";
    return ret;
}

string newLblBlank(string varName) {
    string ret = "JLabel lbl" + varName + " = new JLabel" + "();\n";
    return ret;
}

string addToPanel(string panel, string variable) {
    string ret = panel + ".add(" + variable + ");\n";
    return ret;
}

int main() {
    // Write C++ code here
    int p;
    int emptyJLabelNum = 0;
    int tiposUsados = 0;
    string gridName;
    cout << "Numero de campos: ";
    cin >> p;
    cout << "Nombre del grid: ";
    cin >> gridName;
    
    cout << "t: textField\nc: checkBox\nr: radioButton\nm: comboBox\n";

    string todo = gridName + " = new JPanel(new GridLayout(0, 2, 5, 5));\n\n";
    string declaraciones = "private JPanel " + gridName + ";\n";
    for (int i = 0; i<p; ++i) {
        string campo;
        char tipoCampo;
        cout << p << " Nombre del campo: ";
        cin >> campo;
        string campoCompleto;
        
        cout << "Tipo del campo: ";
        cin >> tipoCampo;
        
        string campoTipo;
        switch(tipoCampo) {
            {
            case 't':
                campoTipo = "txtf" + campo;
                campoCompleto +=
                    newLbl(campo) +
                    addToPanel(gridName, "lbl" + campo) +
                    newJObjectNP("JTextField", campoTipo) +
                    addToPanel(gridName, campoTipo);
                
                declaraciones += "private JTextField txtf" + campo + ";\n";

                tiposUsados = tiposUsados | TEXT_FIELD;
                break;
            }
            {
            case 'c':
                campoTipo = "checkBox" + campo;
                string name = to_string(emptyJLabelNum);
            
                campoCompleto +=
                    newJObject("JCheckBox", "checkBox", campo) +
                    addToPanel(gridName, campoTipo) +
                    
                    newLblBlank(name) +
                    addToPanel(gridName, "lbl" + to_string(emptyJLabelNum));
                
                declaraciones += "private JCheckBox checkBox" + campo + ";\n";
                ++emptyJLabelNum;

                tiposUsados = tiposUsados | CHECK_BOX;
                break;
            }
            {
            case 'r':
                campoTipo = "rdBtn" + campo;
                string campo2;
                cout << p << " Nombre del rd2: ";
                cin >> campo2;
                string campoTipo2 = "rdBtn" + campo2;
                string nombreBtnGroup = "btnGroup" + campo + campo2;
                
                campoCompleto +=
                    newJObjectNP("ButtonGroup", nombreBtnGroup) + "\n" +
                    
                    newJObject("JRadioButton", "rdBtn", campo) +
                    addToPanel(nombreBtnGroup, campoTipo) +
                    addToPanel(gridName, campoTipo) + "\n" +
                
                    newJObject("JRadioButton", "rdBtn", campo2) +
                    addToPanel(nombreBtnGroup, campoTipo2) +
                    addToPanel(gridName, campoTipo2);
                    
                declaraciones += "private JRadioButton rdBtn" + campo + ";\nprivate JRadioButton rdBtn" + campo2 + ";\nprivate ButtonGroup " + nombreBtnGroup + ";\n";
                
                tiposUsados = tiposUsados | RADIO_BTN;
                break;
            }
        {
        case 'm':
        campoTipo = "combo" + campo;
                campoCompleto +=
                    newLbl(campo) +
                    addToPanel(gridName, "lbl" + campo) +
                    newJObjectNP("JComboBox", campoTipo) +
            campoTipo + ".setModel(new DefaultComboBoxModel(new String[] { \"Seleccionar\" }));\n" +
                    addToPanel(gridName, campoTipo);
                declaraciones += "private JComboBox combo" + campo + ";\n";

                tiposUsados = tiposUsados | COMBO_BOX;
                break;
        }
        }
        //getline(cin, campo);
        todo = todo + campoCompleto + '\n';
    }
    char botonSN;
    cout << "Crear botones? S/N\n";
    cin >> botonSN;
    cout << "Imports:\n" <<
	    "import java.awt.GridLayout;\n" <<
	    "import javax.swing.JLabel;\n";
    if (botonSN == 's' || botonSN == 'S') {
        cout << "import java.awt.event.MouseAdapter;\n" <<
                "import java.awt.event.MouseEvent;\n" <<
		"import javax.swing.JButton;\n" <<
		"import javax.swing.ButtonGroup;\n";
        declaraciones += "private JButton btnAceptar;\nprivate JButton btnCancelar;\n";
        todo += "btnAceptar = new JButton(\"Aceptar\");\nbtnAceptar.addMouseListener(new MouseAdapter() {\n@Override\npublic void mouseClicked(MouseEvent e) {\n\n}\n});\n" + gridName + ".add(btnAceptar);\n\nbtnCancelar = new JButton(\"Cancelar\");\nbtnCancelar.addMouseListener(new MouseAdapter() {\n@Override\npublic void mouseClicked(MouseEvent e) {\n\n}\n});\n" + gridName + ".add(btnCancelar);\n";
    }
    if (tiposUsados & TEXT_FIELD)
        cout << "import javax.swing.JTextField;\n";
    if (tiposUsados & CHECK_BOX)
        cout << "import javax.swing.JCheckBox;\n";
    if (tiposUsados & RADIO_BTN)
        cout << "import javax.swing.JRadioButton;\n";
    if (tiposUsados & COMBO_BOX)
        cout << "import javax.swing.JComboBox;\n" <<
                "import javax.swing.DefaultComboBoxModel;\n";
    cout << "\n--------\nDECLARACIONES:\n" << declaraciones << "\n--------\n" << todo << endl;
    cout << "contentPane.add(" << gridName << ");\n";
    return 0;
}

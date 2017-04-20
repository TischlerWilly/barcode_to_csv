#ifndef BIBIOTHEK_OLIVER
#define BIBIOTHEK_OLIVER

#define IST_QT_Projekt //Diese Zeile ausblenden wenn kein QT-Projekt



#include <string>
#include <sstream>

std::string int_zu_string(int zahl);


#ifdef IST_QT_Projekt
    #include <QString>

    QString int_zu_qstring(int zahl);

#endif //IST_QT_Projekt





#endif // BIBIOTHEK_OLIVER


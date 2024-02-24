# Skribbl
Proiect Skribbl - Modern C++

# Descriere functionalitate

  <p>Este o aplicatie client-server care lucreaza cu o baza de date. In momentul in care se ruleaza aplicatia se deschide o pagina login in care user-ul trebuie sa-si introduca username-ul si parola, acestea fiind existente in baza de date.</p>
  <p>Daca user-ul nu are un cont creat, acesta poate sa se inregistreze intr-o fereasta separata. Username-ul trebuie sa fie unic, iar parola trebuie sa aiba cel putin 8 caractere, cel putin o litera mare, o litera mica , un numar si un caracter special.</p>
  <p>O data ajuns in meniu, user-ul are o varietate de optiuni, precum poate sa-si verifice profilul, poate vedea istoricul jocurilor si poate selecta iconita. O alta optiune ar fi shop-ul, unde acesta poate sa achizitioneze iconite in functie de monedele pe care le are, acestea putand fi obtinute in functie de punctajul dintr-un meci. User-ul poate sa creeze un joc sau sa participe la un lobby deja creat prin utilizarea unui cod obtinut la crearea lobby-ului.</p>
	<p>Dupa ce toti jucatorii au intrat in lobby, liderul poate sa porneasca jocul. Jocul dureaza 4 runde, fiecare runda avand un numar de subrunde in functie de cati jucatori sunt in lobby. La inceputul unei subrunde, un jucator este numit desenator si poate alege din 3 cuvinte selectate random din baza de date, iar dupa incepe procesul de desenare care dureaza cel mult 60 de secunde, in care ceilalti jucatori trebuie sa ghiceasca cuvantul ales. Dupa terminarea timpului, fiecare jucator primeste un anumit scor, calculat in functie de secundele in care a ghicit, iar pentru desenator se calculeaza media secundelor in care au ghicit fiecare jucator.</p>
 <p>La sfarsitul rundelor, se afiseaza un clasament in functie de numarul de puncte acumulate pe parcurs de fiecare jucator.</p>

# Componente C++ Modern
<ol>
<li>const ref</li>
<li>move semantics</li>
<li>structuri de date moderne</li>
<li>ranges</li>
<li>algoritmi moderni</li>
<li>smart pointers</li>
<li>templates</li>
<li>regex</li>
<li>DLL</li>
<li>lambdas</li>
</ol>

 
# Componente avansate 

<ol>
<li>GUI- interfata grafica folosita pentru a vizualiza functionalitatile jocului.( Am folosit Qt Framework)</li>
<li>Retelistica- Comunicarea dintre client si serever.( Am folosit Crow si CPR)</li>
<li>Baze de date- Stocarea datelor( Am folosit SQLite ORM) </li>
</ol> 






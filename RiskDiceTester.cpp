/**
 * \brief     Test if is better to defend in Risk game with one or more dice.
 * \details   This class is used to demonstrate the advantage of using more dice to defend.
 * \author    Rafael J. Vicente
 * \version   1.0
 * \copyright GNU Public License.
 */

#include <iostream>
#include <sstream>
#include <list>
#include <random>

using namespace std;

/** \brief Create two random rolling dices arrays and checks the advantage for attacker depending on how many dice use the defender
 *
 * \tparam MAXSIZE size for the two arrays of random rolling dices
 */
template<size_t MAXSIZE = 3000>
class RiskDiceTester
{
  private:
    using Die_t = unsigned char; // Numbers 1-6

    Die_t * attackerArray;
    Die_t * defenderArray;

  public:
    RiskDiceTester()
    {
      attackerArray = new Die_t[MAXSIZE];
      defenderArray = new Die_t[MAXSIZE];

      //Random seed
      random_device rd;
      mt19937 mt(rd());
      uniform_int_distribution<int> dist(1, 6);

      for (size_t i = 0; i < MAXSIZE; ++i)
      {
        attackerArray[i] = dist(mt);
        defenderArray[i] = dist(mt);
      }
    }

    ~RiskDiceTester()
    {
      delete[] attackerArray;
      delete[] defenderArray;
    }

    /** \brief Prints the arrays in two rows corresponding two each array
     *
     * \param[in] size of the array that you want to print
     */
    void PrintArrays(size_t size)
    {
      size = size < MAXSIZE ? size : MAXSIZE;
      stringstream ssDef;

      // First iteration with no space
      cout << static_cast<unsigned>(attackerArray[0]);
      ssDef << static_cast<unsigned>(defenderArray[0]);

      for (unsigned int i = 1; i < size; ++i)
      {
        cout << ' ' << static_cast<unsigned>(attackerArray[i]);
        ssDef << ' ' << static_cast<unsigned>(defenderArray[i]);
      }

      cout << endl << ssDef.str() << endl;
    }

    /** \brief Prints the arrays in two rows corresponding two each array
     *
     * \param[in] attackerDice number of dice to use as attacker
     * \param[in] defenderDice number of dice to use as defender
     */
    void CalculateWins(unsigned char attackerDice, unsigned char defenderDice)
    {
      int attackerCounter = 0, defenderCounter = 0;
      const size_t limit = MAXSIZE / (attackerDice > defenderDice ? attackerDice : defenderDice);
      for (size_t i = 0; i < limit; ++i)
      {
        list<Die_t> attackerList, defenderList;

        for (auto d = 0; d < attackerDice; ++d)
          attackerList.push_back(attackerArray[i * attackerDice + d]);
        attackerList.sort();

        for (auto d = 0; d < defenderDice; ++d)
          defenderList.push_back(defenderArray[i * defenderDice + d]);
        defenderList.sort();

        while (defenderList.size() != 0 && attackerList.size() != 0)
        {
          auto defenderAux = defenderList.back();
          defenderList.pop_back();
          auto attackerAux = attackerList.back();
          attackerList.pop_back();

          defenderAux >= attackerAux ? ++defenderCounter : ++attackerCounter;
        }
      }

      cout  << endl;
      cout << "For " << static_cast<unsigned>(attackerDice) << " attacker dice and " << static_cast<unsigned>(defenderDice) << " defender dice:" << endl;
      cout << "Attacker won: " << attackerCounter << " times" << endl;
      cout << "Defender won: " << defenderCounter << " times" << endl;
      auto percentile = round((static_cast<float>(attackerCounter) / defenderCounter - 1) * 100);
      cout << "Attacker advantage: " << percentile << "%" << endl;
    }

};

int main()
{
  RiskDiceTester<3000000> (r);
  r.PrintArrays(50); //Tests arrays are well allocated and generated
  r.CalculateWins(3, 2);
  r.CalculateWins(3, 1);

  return 0;
}

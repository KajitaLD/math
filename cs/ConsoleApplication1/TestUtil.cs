using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    public class TestUtil
    {
        static int PASSED  = 0;
        static int FAILED  = 0;
        static int QUESTION  = 0;
        static int SKIPPED  = 0;

        static int ALL_PASSED   = 0;
        static int ALL_FAILED   = 0;
        static int ALL_QUESTION = 0;
        static int ALL_SKIPPED = 0;

        public TestUtil()
        {
        }
        public static void COMPARE<T>(T a, T b)
            where T : IComparable
        {
            try
            {
                if (a.CompareTo(b) == 0)
                {
                    PASSED++;
                    System.Diagnostics.StackTrace st = new System.Diagnostics.StackTrace();
                    Console.WriteLine("PASS: " + st.GetFrame(1).GetMethod());
                }
                else
                {
                    if (a.ToString() == b.ToString())
                    {
                        QUESTION++;
                        System.Diagnostics.StackTrace st = new System.Diagnostics.StackTrace();
                        Console.WriteLine("QUESTION: " + st.GetFrame(1).GetMethod());
                        Console.WriteLine(" expected: " + a.ToString());
                        Console.WriteLine(" actual: " + b.ToString());
                    }
                    else
                    {
                        FAILED++;
                        System.Diagnostics.StackTrace st = new System.Diagnostics.StackTrace();
                        Console.WriteLine("FAILED: " + st.GetFrame(1).GetMethod() + " Compared values are not the same");
                        Console.WriteLine(" expected: " + a.ToString());
                        Console.WriteLine(" actual: " + b.ToString());
                    }
                }
            }
            catch (Exception ex)
            {
                SKIPPED++;
                System.Diagnostics.StackTrace st = new System.Diagnostics.StackTrace();
                Console.WriteLine("SKIPPED: " + st.GetFrame(1).GetMethod() + ex.Message);

            }
        }

        public static void VERIFY(bool go)
        {
            try
            {
                if (go)
                {
                    PASSED++;
                    System.Diagnostics.StackTrace st = new System.Diagnostics.StackTrace();
                    Console.WriteLine("PASS: " + st.GetFrame(1).GetMethod());
                }
                else
                {
                    FAILED++;
                    System.Diagnostics.StackTrace st = new System.Diagnostics.StackTrace();
                    Console.WriteLine("FAILED: " + st.GetFrame(1).GetMethod() + " Verified value but failed.");
                }
            }
            catch (Exception ex)
            {
                SKIPPED++;
                System.Diagnostics.StackTrace st = new System.Diagnostics.StackTrace();
                Console.WriteLine("SKIPPED: " + st.GetFrame(1).GetMethod() + ex.Message);

            }
        }



        public static void LDTEST<Test>(Test t)
            where Test : ITest
        {
            try
            {
                
                PASSED = FAILED = SKIPPED = QUESTION = 0;
                Console.WriteLine("********* Start testing of " + t.GetType().ToString() + " *********");
                t.test();
                Console.WriteLine("Totals: " + PASSED.ToString() + " passed, " + FAILED.ToString() + " failed, " + QUESTION.ToString() + " questioned.");
                Console.WriteLine("********* Finished testing of " + t.GetType().ToString() + " *********");
                ALL_PASSED += PASSED;
                ALL_FAILED += FAILED;
                ALL_QUESTION += QUESTION;
                ALL_SKIPPED += SKIPPED;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message + ex.StackTrace);
            }
        }
        public static void SCORE()
        {
            try
            {
                Console.WriteLine("********* Final Score *********");
                Console.WriteLine("Totals: " + ALL_PASSED.ToString() + " passed, " + ALL_FAILED.ToString() + " failed, " + ALL_QUESTION.ToString() + " questioned, " + ALL_SKIPPED.ToString() + " skipped.");
                Console.WriteLine("********* Finished *********");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message + ex.StackTrace);
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Drawing;

namespace Ütemezés
{
    public partial class MainForm : Form
    {

        private static int processIndex = 0;
        List<string[]> processesList = new List<string[]>();
        string[][] processes;
        string[][] ganttProcesses;
        private int columns;
        private bool usedRR = false;
        private bool ganttOpen = false;


        public MainForm()
        {
            InitializeComponent();
            StartStuff();
        }

        public void StartStuff()
        {
            processList.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
            columns = processList.Columns.Count;
        }

        private void AddNewProcess(object sender, EventArgs e)
        {
            if(!ganttOpen)
            {
                AddProcess processForm = new AddProcess(Width * 2 / 3, (int)(Height * 0.45), processIndex + 1);
                if (processForm.ShowDialog() == DialogResult.OK)
                {
                    string[] processDetails = new string[columns];


                    processDetails[0] = (processIndex + 1).ToString();
                    processDetails[1] = processForm.Arrive;
                    processDetails[2] = processForm.CPU_time;

                    ListViewItem lvi = new ListViewItem(processDetails);
                    lvi.Text = "P" + processDetails[0];
                    processList.Items.Add(lvi);

                    processesList.Add(processDetails);

                    processIndex++;

                }
                processForm.Dispose();
                ganttDiagram.Enabled = false;
            }
           
        }

        private void FirstComeFirstServe(object sender, EventArgs e)
        {
            if (processesList.Count != 0 && !usedRR && !ganttOpen)
            {
                CollectInfo();
                processes = SortArray(processes, 1, 2, 0, processes.Length - 1);
                processList.Items.Clear();
                FullCalculate(processes);


                for (int i = 0; i < processes.Length; i++)
                {
                    ListViewItem lvi = new ListViewItem(processes[i]);
                    lvi.Text = "P" + processes[i][0];
                    processList.Items.Add(lvi);
                }

                processList.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);

                ganttProcesses = processes;
                ganttDiagram.Enabled = true;
            }
        }

        private void ShortestJobFirst(object sender, EventArgs e)
        {
            if (processesList.Count != 0 && !usedRR && !ganttOpen)
            {
                CollectInfo();
                processes = SortArray(processes, 2, 1, 0, processes.Length - 1);

                string[][] processesInOrder = new string[processes.Length][];
                bool[] chosen = new bool[processes.Length];
                for (int i = 0; i < chosen.Length; i++)
                {
                    chosen[i] = false;
                }
                for (int i = 0; i < processesInOrder.Length; i++)
                {
                    int actualTime;
                    if (i == 0)
                    {
                        actualTime = 0;
                    }
                    else
                    {
                        actualTime = int.Parse(processesInOrder[i - 1][4]);
                    }
                    bool found = false;
                    int minIndex = 0;
                    for (; chosen[minIndex]; minIndex++) ;
                    for (int j = 0; j < processes.Length && !found; j++)
                    {
                        if (!chosen[j] && int.Parse(processes[j][1]) <= actualTime)
                        {
                            chosen[j] = true;
                            found = true;
                            processesInOrder[i] = processes[j];
                        }
                        if (!chosen[j] && SJFLess(processes[j], processes[minIndex]))
                        {
                            chosen[j] = true;
                            minIndex = j;
                        }
                    }
                    if (!found)
                    {
                        chosen[minIndex] = true;
                        processesInOrder[i] = processes[minIndex];
                    }
                    Calculate(processesInOrder, i);
                }

                processList.Items.Clear();


                for (int i = 0; i < processesInOrder.Length; i++)
                {
                    ListViewItem lvi = new ListViewItem(processesInOrder[i]);
                    lvi.Text = "P" + processesInOrder[i][0];
                    processList.Items.Add(lvi);
                }
                processList.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);

                ganttProcesses = processesInOrder;
                ganttDiagram.Enabled = true;
            }

        }

        private bool SJFLess(string[] process1, string[] process2)
        {
            int p1Arrive = int.Parse(process1[1]);
            int p2Arrive = int.Parse(process2[1]);
            int p1CPU = int.Parse(process1[2]);
            int p2CPU = int.Parse(process2[2]);
            if (p1Arrive < p2Arrive)
            {
                return true;
            }
            else if (p1Arrive == p2Arrive)
            {
                if (p1CPU < p2CPU)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        private void RoundRobin(object sender, EventArgs e)
        {
            int ms = (int)numericUpDown1.Value;
            if (ms != 0 && processesList.Count != 0 && !ganttOpen && !usedRR)
            {
                usedRR = true;
                CollectInfo();
                processList.Items.Clear();
                processes = SortArray(processes, 1, -1, 0, processes.Length - 1);

                List<string[]> partProcesses = new List<string[]>();
                CopyToList(processes, partProcesses);                
                partProcesses = RRSort(partProcesses, ms);

                processes = MergeProcesses(processes, partProcesses);

                for (int i = 0; i < processes.Length; i++)
                {
                    ListViewItem lvi = new ListViewItem(processes[i]);
                    lvi.Text = "P" + processes[i][0];
                    processList.Items.Add(lvi);
                }

                processList.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);

                ganttProcesses = partProcesses.ToArray();
                ganttDiagram.Enabled = true;
            }
        }

        private void CopyToList(string[][] array, List<string[]> list)
        {
            foreach(string[] stringArray in array)
            {
                string[] toAdd = new string[stringArray.Length];
                for(int i = 0; i<stringArray.Length; i++)
                {
                    toAdd[i] = stringArray[i];
                }
                list.Add(toAdd);
            }
        }

        private void CollectInfo()
        {
            processes = new string[processList.Items.Count][];
            processes = processesList.ToArray();
        }

        private List<string[]> RRSort(List<string[]> partProcesses, int ms)
        {
            for(int i = 0; i<partProcesses.Count; i++)
            {
                if (int.Parse(partProcesses[i][2]) > ms)
                {
                    string[] splitProcess = new string[columns];
                    splitProcess[0] = partProcesses[i][0];
                    splitProcess[2] = (int.Parse(partProcesses[i][2]) - ms).ToString();
                    partProcesses[i][2] = ms.ToString();

                    partProcesses[i] = Calculate(partProcesses.ToArray(), i);

                    splitProcess[1] = partProcesses[i][4];
                    partProcesses[i][2] = (int.Parse(splitProcess[2]) + ms).ToString();
                    
                    

                    partProcesses.Add(splitProcess);

                    partProcesses = SortArray(partProcesses.ToArray(), 1, -1, 0, partProcesses.Count - 1).ToList();

                }
                else
                {
                    partProcesses[i] = Calculate(partProcesses.ToArray(), i);
                }
               
               
            }
            return partProcesses;
        }

        private string[][] MergeProcesses(string[][] processes, List<string[]> partProcesses)
        {
            //0 - "pid"
            //1 - Érkezés
            //2 - CPU-idő
            //3 - Indulás
            //4 - befejezés
            //5 - várakozás
            //6 - körülfordulási idő
            //7 - válaszidő

            bool[] first = new bool[processes.Length];
            for (int i = 0; i < first.Length; i++)
            {
                first[i] = true;
            }
            foreach (string[] process in partProcesses)
            {
                int i = int.Parse(process[0]) - 1;
                if (!first[i])
                {
                    processes[i][1] += ", ";
                    processes[i][2] += ", ";
                    processes[i][3] += ", ";
                    processes[i][4] += ", ";
                    processes[i][5] += ", ";

                    
                    processes[i][6] = (int.Parse(processes[i][6]) + int.Parse(process[6])).ToString();
                    processes[i][1] += process[1];
                    processes[i][2] += process[2];
                }
                else
                {
                    processes[i][6] = process[6];
                    first[i] = false;
                    processes[i][7] = process[7];
                }
                
                processes[i][3] += process[3];
                processes[i][4] += process[4];
                processes[i][5] += process[5];

            }
            return processes;
        }

        /// <summary>
        /// Merge-sorting
        /// </summary>
        /// <param name="array">Two-dimensional array to sort</param>
        /// <param name="compareColumnIndex">Data-column to sort by (convertable to int)</param>
        /// <param name="startIndex"></param>
        /// <param name="endIndex"></param>
        private string[][] SortArray(string[][] array, int compareColumnIndex, int secondaryCompareColumnIndex, int startIndex, int endIndex)
        {
            if (startIndex < endIndex)
            {
                int middle = (startIndex + endIndex) / 2;
                string[][] array1 = SortArray(array, compareColumnIndex, secondaryCompareColumnIndex, startIndex, middle);
                string[][] array2 = SortArray(array, compareColumnIndex, secondaryCompareColumnIndex, middle + 1, endIndex);
                array = Merge(array1, array2, compareColumnIndex, secondaryCompareColumnIndex);
                return array;

            }
            else
            {
                string[][] smallArray = new string[1][];
                smallArray[0] = array[startIndex];
                return smallArray;
            }



        }
        private string[][] Merge(string[][] array1, string[][] array2, int compareColumnIndex, int secondaryCompareColumnIndex)
        {
            string[][] mergedArray = new string[array1.Length + array2.Length][];
            int i = 0, j = 0;
            while (i < array1.Length && array2.Length > j)
            {
                int a1 = int.Parse(array1[i][compareColumnIndex]);
                int a2 = int.Parse(array2[j][compareColumnIndex]);
                if (secondaryCompareColumnIndex < 0)
                {
                    if (a1 <= a2)
                    {
                        mergedArray[i + j] = array1[i];
                        i++;
                    }
                    else if (a1 > a2)
                    {
                        mergedArray[i + j] = array2[j];
                        j++;
                    }
                }
                else
                {
                    if (a1 < a2)
                    {
                        mergedArray[i + j] = array1[i];
                        i++;
                    }
                    else if (a1 > a2)
                    {
                        mergedArray[i + j] = array2[j];
                        j++;
                    }
                    else
                    {
                        a1 = int.Parse(array1[i][secondaryCompareColumnIndex]);
                        a2 = int.Parse(array2[j][secondaryCompareColumnIndex]);
                        if (a1 <= a2)
                        {
                            mergedArray[i + j] = array1[i];
                            i++;
                        }
                        else
                        {
                            mergedArray[i + j] = array2[j];
                            j++;
                        }
                    }
                }
                
            }

            while (array1.Length > i)
            {
                mergedArray[i + j] = array1[i];
                i++;
            }
            while (array2.Length > j)
            {
                mergedArray[i + j] = array2[j];
                j++;
            }
            return mergedArray;
        }
        
        private string[][] FullCalculate(string[][] processArray)
        {
            for(int i = 0; i<processArray.Length; i++)
            {
                processArray[i] = Calculate(processArray, i);
            }
            return processArray;
        }
        private string[] Calculate(string[][] processArray, int index)
        {
            //0 - "pid"
            //1 - Érkezés
            //2 - CPU-idő
            //3 - Indulás
            //4 - befejezés
            //5 - várakozás
            //6 - körülfordulási idő
            //7 - válaszidő

            if (index == 0)
            {
                processArray[0][3] = processArray[0][1];
            }
            else
            {
                if (int.Parse(processArray[index - 1][4]) <= int.Parse(processArray[index][1]))
                {
                    processArray[index][3] = processArray[index][1];
                }
                else
                {
                    processArray[index][3] = processArray[index - 1][4];
                }
            }

            processArray[index][4] = (int.Parse(processArray[index][3]) + int.Parse(processArray[index][2])).ToString();
            processArray[index][5] = (int.Parse(processArray[index][3]) - int.Parse(processArray[index][1])).ToString();
            processArray[index][6] = (int.Parse(processArray[index][4]) - int.Parse(processArray[index][1])).ToString();
            processArray[index][7] = processArray[index][5];

            return processArray[index];
        }
        private void ResetList(object sender, EventArgs e)
        {
            processesList.Clear();
            processList.Items.Clear();
            processIndex = 0;
            usedRR = false;
            ganttDiagram.Enabled = false;
        }

        private void GenerateGantt(object sender, EventArgs e)
        {
            ganttOpen = true;
            Form ganttForm = new Form();
            ganttForm.Height = Height;
            ganttForm.Width = Screen.GetWorkingArea(new Point(0, 0)).Width;
            ganttForm.StartPosition = FormStartPosition.CenterScreen;
            ganttForm.FormClosed += GanttClosed;
            ganttForm.AutoScroll = true;
            ganttForm.Text = "Gantt diagram";

            Gantt diagram = new Gantt(ganttProcesses, processIndex + 1, ganttForm);

            ganttDiagram.Enabled = false;

            ganttForm.Show();
        }
        private void GanttClosed(object sender, EventArgs e)
        {
            ganttOpen = false;
            ganttDiagram.Enabled = true;
            ((Form)sender).Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Info info = new Info("Keresztes Iulia, Miskolci Egyetem, Informatika Intézet, 101juliakeresztes@gmail.com",
                2*Width / 6, Height / 3);
            info.ShowDialog();
            
        }
    }
}

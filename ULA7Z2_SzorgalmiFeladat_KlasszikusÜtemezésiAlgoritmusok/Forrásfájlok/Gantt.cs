using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace Ütemezés
{
    class Gantt : TableLayoutPanel
    {
        string[][] processes;
        int length;
        int processNumber;

        public Gantt(string[][] processes, int processIndex, Control parent)
        {
            this.processes = processes;
            length = int.Parse(processes[processes.Length - 1][4]);
            processNumber = processIndex;

            Parent = parent;
            AutoScroll = true;

            ColumnCount = length + 1;
            RowCount = processIndex+1;
            CellBorderStyle = TableLayoutPanelCellBorderStyle.Single;
            Dock = DockStyle.Fill;

            SetColumns();
            SetRows();

            SetLabels();
            SetNumberLabels();



            SetActivity();

        }

        

        private void SetColumns()
        {
            int percent = 100 / ColumnCount;
            for (int i = 0; i <= ColumnCount; i++)
            {
                ColumnStyles.Add(new ColumnStyle(SizeType.Percent,percent));
            }
        }
        private void SetRows()
        {
            for(int i = 0; i <= RowCount; i++)
            {
                RowStyles.Add(new RowStyle(SizeType.AutoSize));
            }
        }



        private void SetLabels()
        {
            for(int i = 0; i<processNumber - 1; i++)
            {
                Label processLabel = new Label();
                processLabel.Text = "P" + (i + 1);
                processLabel.Dock = DockStyle.Fill;
                Controls.Add(processLabel, 0, i);
            }
        }
        private void SetNumberLabels()
        {
            for(int i = 0; i<ColumnCount; i++)
            {
                Label number = new Label();
                number.AutoSize = true;
                number.Text = i.ToString();
                Controls.Add(number, i, RowCount - 1);
                number.Dock = DockStyle.Right;
            }
        }
        private void SetActivity()
        {
            foreach (string[] process in processes)
            {
                Panel active = new Panel();
                active.Dock = DockStyle.Fill;
                active.BackColor = System.Drawing.Color.Gold;

                int start = int.Parse(process[3]);
                int finish = int.Parse(process[4]);
                int span = finish - start;
                int processIndex = int.Parse(process[0]) - 1;

                Controls.Add(active, start + 1, processIndex);
                SetColumnSpan(active, span);

                Panel inactive = new Panel();
                inactive.Dock = DockStyle.Fill;
                inactive.BackColor = System.Drawing.Color.LightGray;

                int arrive = int.Parse(process[1]);
                span = start - arrive;

                if (span != 0)
                {
                    Controls.Add(inactive, arrive + 1, processIndex);
                    SetColumnSpan(inactive, span);
                }
                
            }
        }
    }
}

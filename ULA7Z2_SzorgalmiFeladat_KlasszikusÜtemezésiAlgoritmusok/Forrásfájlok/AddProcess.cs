using System;
using System.Drawing;
using System.Windows.Forms;

namespace Ütemezés
{
    class AddProcess : Form
    {
        TableLayoutPanel data;
        Label process;
        NumericUpDown arrive;
        NumericUpDown CPU;

        Button add;

        public string Arrive
        {
            get
            {
                return arrive.Value.ToString();
            }
        }

        public string CPU_time
        {
            get
            {
                return CPU.Value.ToString();
            }
        }


        public AddProcess(int width, int height, int index)
        {
            Width = width;
            Height = height;
            MinimumSize = new Size(width / 3, height / 3);
            StartPosition = FormStartPosition.CenterScreen;
            InitializeComponents(index);

        }

        private void InitializeComponents(int index)
        {
            data = new TableLayoutPanel();
            process = new Label();
            arrive = new NumericUpDown();
            CPU = new NumericUpDown();

            add = new Button();

            this.Padding = new Padding(Height / 20);


            SetDataTable();

            SetProcessLabel(index);
            SetArriveEnter();
            SetCPUEnter();

            SetAddButton();
        }


        private void SetDataTable()
        {

            data.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 33));
            data.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 33));
            data.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 33));

            data.RowStyles.Add(new RowStyle(SizeType.Percent, 33));
            data.RowStyles.Add(new RowStyle(SizeType.Percent, 33));
            data.RowStyles.Add(new RowStyle(SizeType.Percent, 33));

            data.ColumnCount = 3;
            data.RowCount = 2;
            data.Dock = DockStyle.Fill;

            data.Parent = this;
            SetNameLabels();
        }

        private void SetNameLabels()
        {
            Label processName = new Label();
            processName.Text = "Processz";
            processName.Dock = DockStyle.Fill;
            processName.TextAlign = ContentAlignment.MiddleCenter;

            Label arriveLabel = new Label();
            arriveLabel.Text = "Beérkezés";
            arriveLabel.Dock = DockStyle.Fill;
            arriveLabel.TextAlign = ContentAlignment.MiddleCenter;

            Label CPULabel = new Label();
            CPULabel.Text = "CPU-idő";
            CPULabel.Dock = DockStyle.Fill;
            CPULabel.TextAlign = ContentAlignment.MiddleCenter;


            data.Controls.Add(processName, 0, 0);
            data.Controls.Add(arriveLabel, 1, 0);
            data.Controls.Add(CPULabel, 2, 0);


        }
        private void SetProcessLabel(int index)
        {
            process.Text = "P" + index;
            process.Dock = DockStyle.Fill;
            process.TextAlign = ContentAlignment.MiddleCenter;

            data.Controls.Add(process);
        }
        private void SetArriveEnter()
        {
            arrive.Minimum = 0;
            data.Controls.Add(arrive);
            arrive.Anchor = (AnchorStyles.Top | AnchorStyles.Left);
            arrive.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            arrive.Anchor = AnchorStyles.None;
            arrive.DecimalPlaces = 0;
        }
        private void SetCPUEnter()
        {
            CPU.Minimum = 1;
            data.Controls.Add(CPU);
            CPU.Anchor = (AnchorStyles.Top | AnchorStyles.Left);
            CPU.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            CPU.Anchor = AnchorStyles.None;
            CPU.DecimalPlaces = 0;
        }

        void SetAddButton()
        {
            add.Text = "Hozzáadás";
            add.Click += AddProcessClick;
            add.Size = CPU.Size;
            data.Controls.Add(add, 2, 2);
            add.Anchor = (AnchorStyles.Top | AnchorStyles.Left);
            add.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right);
            add.Anchor = AnchorStyles.None;

        }

        void AddProcessClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            this.Close();
        }


    }
}

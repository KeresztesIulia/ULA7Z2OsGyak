using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace Ütemezés
{
    class Info : Form
    {
        public Info(string information, int width, int height)
        {
            Width = width;
            Height = height;
            Text = "Névjegy";

            Label infoLabel = new Label();
            infoLabel.Text = information;
            infoLabel.Dock = DockStyle.Fill;
            infoLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;

            Controls.Add(infoLabel);
            StartPosition = FormStartPosition.CenterScreen;
        }
    }
}

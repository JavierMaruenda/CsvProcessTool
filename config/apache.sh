
# Set location of html directory
# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Set the location of the html folder
HTML_DIR="$SCRIPT_DIR"/../html

# Make Apache configuration files writable
sudo chmod +w /etc/apache2/sites-available/000-default.conf
sudo chmod +w /etc/apache2/apache2.conf

# Modify Apache config files
# Check if <Directory> block already exists in Apache configuration
if ! grep -q "<Directory $HTML_DIR>" /etc/apache2/apache2.conf; then
    # Add to Apache configuration file
    echo "
    <Directory $HTML_DIR>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
        Options +ExecCGI
        AddHandler cgi-script .cgi .pl .py
    </Directory>
    " | sudo tee -a /etc/apache2/apache2.conf > /dev/null
fi

# Set new directory as default serving directory
sudo sed -i "s|^\(\s*\)DocumentRoot.*|\1DocumentRoot $HTML_DIR|" /etc/apache2/sites-available/000-default.conf

# Restart Apache
sudo systemctl restart apache2

echo "Apache serving directory $HTML_DIR added to cofig file and set as default"



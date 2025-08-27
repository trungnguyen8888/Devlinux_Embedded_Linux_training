#==========================================================================================================
# Start of file
#==========================================================================================================
#==========================================================================================================
# Imports
#==========================================================================================================
import os
import sys
import subprocess
from pathlib import Path
from colorama import Fore, Style
from typing import Callable
from PySide6.QtWidgets import (
    QApplication,   # Core application object & event loop (one per process)
    QWizard,        # Multi-step dialog container (Back/Next/Finish flow)
    QWizardPage,    # A single step/page within a QWizard
    QVBoxLayout,    # Vertical layout manager (stacks child widgets top→bottom)
    QLabel,         # Non-editable text/image display label
    QCheckBox,      # For creating checkboxes (supports tri-state if needed)
    QMessageBox     # For creating modal message dialog (info/warning/critical/questions)
)

#==========================================================================================================
# User-defined data
#==========================================================================================================
# Document type to build
doc = "Document"

#==========================================================================================================
# Fixed data (Do not change ;) )
#==========================================================================================================
# Result of execution
SUCCESS = 0
FAILURE = (-1)

#==========================================================================================================
# Classes
#==========================================================================================================
#==========================================================================================================
# Class:        Info
# Description:  Store common information about the build commands between HTML and PDF.
# Retval:       None.
#==========================================================================================================
class Info:
    """
    Start of class
    """

    def __init__(self, file_type: str):
        self._work_dir      = os.getcwd()
        self._safe_mode     = "unsafe"
        self._input_path    = f"{self._work_dir}/doc/asciidoc"
        self._output_path   = f"{self._work_dir}/doc"
        self._output_file   = f"{self._output_path}/{doc}.{file_type}"
        self._asciidoc_file = "body.adoc"

    # The working directory
    @property
    def work_dir(self): return self._work_dir

    # Safe mode
    @property
    def safe_mode(self): return self._safe_mode

    # Directory to store AsciiDoctor files
    @property
    def input_path(self): return self._input_path

    # Directory to store generated documents
    @property
    def output_path(self): return self._output_path

    # Generated document
    @property
    def output_file(self): return self._output_file

    # AsciiDoctor file (body.adoc)
    @property
    def asciidoc_file(self): return self._asciidoc_file

    """
    End of class
    """

#==========================================================================================================
# Class:        HTML_Info
# Description:  This class inherits from class Info and also, stores private information about HTML.
# Retval:       None.
#==========================================================================================================
class HTML_Info(Info):
    """
    Start of class
    """

    def __init__(self):
        super().__init__("html")
        self._build_html_tool = "asciidoctor"
        self._html_style_path = str(Path(__file__).resolve().parent.parent.parent)
        self._html_style      = "styles.css"

    # Tool to build HTML (asciidoctor)
    @property
    def build_html_tool(self): return self._build_html_tool

    # Path of style file for HTML
    @property
    def html_style_path(self): return self._html_style_path

    # Style file for HTML
    @property
    def html_style(self): return self._html_style

    """
    End of class
    """

#==========================================================================================================
# Class:        PDF_Info
# Description:  This class inherits from class Info and also, stores private information about PDF.
# Retval:       None.
#==========================================================================================================
class PDF_Info(Info):
    """
    Start of class
    """

    def __init__(self):
        super().__init__("pdf")
        self._build_pdf_tool  = "asciidoctor-pdf"
        self._pdf_themes_path = str(Path(__file__).resolve().parent.parent.parent)
        self._pdf_theme       = "theme.yml"

    # Tool to build PDF (asciidoctor-pdf)
    @property
    def build_pdf_tool(self): return self._build_pdf_tool

    # Path of theme file for PDF
    @property
    def pdf_themes_path(self): return self._pdf_themes_path

    # Theme file for PDF
    @property
    def pdf_theme(self): return self._pdf_theme

    """
    End of class
    """

#==========================================================================================================
# Functions
#==========================================================================================================
#==========================================================================================================
# Function:     ensure_output_dir
# Description:  Check if the path specified by 'str' or Path (pathlib) exits. If it does not exit, it will
#               be created. If it exists, it doesn't return error due to exist_ok = True. And also, if
#               parents does not exist, create parents.
# Retval:       None (due to -> None).
#==========================================================================================================
def ensure_output_dir(
        path: (str | Path)  # Path in the form of string or returned from Path()
) -> None:  # Type of return value
    """
    Start of function
    """
    
    # Create folder if needed
    Path(path).mkdir(parents = True, exist_ok = True)
    
    """
    End of function
    """

    # Return
    return None

#==========================================================================================================
# Function:     run_cmd
# Description:  Run the command stored in the list.
# Retval:       Tuple of result of command execution and log with leading and trailing whitespaces removed.
#==========================================================================================================
def run_cmd(
        args: list[str]     # Command to execute
) -> tuple[int, str]:   # Type of return value
    """
    Start of function
    """

    result = SUCCESS

    # Run the command, decode output from binary to text (text = True)
    # and redirect result to Python, stored in cp.stdout, cp.stderr (capture_output = True)
    cp = subprocess.run(args, text = True, capture_output = True)

    # Save the result of the command execution: True/False
    if (SUCCESS != cp.returncode):
        result = FAILURE

    # Get the message log and remove leading and trailing whitespaces
    message = (cp.stdout or "") + (cp.stderr or "")
    message = message.strip()

    """
    End of function
    """

    # Return result
    return (result, message)

#==========================================================================================================
# Function:     check_required_files
# Description:  Check if style.css and theme.yml are present in their respective correct locations.
# Retval:       Info of required file existence: ["result"] = SUCCESS or FAILURE.
#==========================================================================================================
def check_required_files(
        for_html: bool,                         # True: for HTML; False: for PDF
        common_info: Info,                      # Common information for both HTML and PDF
        html_info: HTML_Info | None = None,     # HTML private information. Default: None
        pdf_info: PDF_Info | None = None        # PDF private information. Default: None
) -> dict[str, (str | int)]:    # Type of return value
    """
    Start of function
    """

    """
    - Always check body.adoc in ./doc/ (since input_path = CWD/doc)
    - If for_html = True  => also check styles.css (relative to this script)
    - If for_html = False => also check theme.yml  (relative to this script)
    """

    result = {
        "result"  : SUCCESS,
        "message" : ""
    }

    # body.adoc expected at ./doc/ relative to CWD (since input_path = CWD/doc)
    body_path = Path(common_info.input_path)/common_info.asciidoc_file
    if not body_path.exists():
        result["result"] = FAILURE
        result["message"] = f"Missing required file: {body_path}"
    
    if (SUCCESS == result["result"]):
        # For HTML, check the existence of styles.css
        if for_html is True and html_info is not None:
            # styles.css two-levels up from this script file (../../../styles.css)
            styles_path = Path(__file__).resolve().parent/html_info.html_style_path/html_info.html_style
            styles_path = styles_path.resolve()

            if styles_path.exists() is not True:
                result["result"] = FAILURE
                result["message"] = f"Missing required file: {styles_path}"
        # For PDF, check the existence of theme.yml (../../../theme.yml)
        elif for_html is False and pdf_info is not None:
            theme_path = Path(__file__).resolve().parent/pdf_info.pdf_themes_path/pdf_info.pdf_theme
            theme_path = theme_path.resolve()

            if theme_path.exists() is not True:
                result["result"] = FAILURE
                result["message"] = f"Missing required file: {theme_path}"
        else:
            # Do nothing
            pass
    else:
        # Do nothing
        pass

    """
    End of function
    """
    
    # Return
    return result

#==========================================================================================================
# Function:     build_html
# Description:  Build document in HTML format.
# Retval:       Info of build result.
#==========================================================================================================
def build_html(
) -> tuple[int, str]:  # Type of return value
    """
    Start of function
    """

    # Get HTML information
    info = HTML_Info()

    # Check foler doc existence and create it if needed
    ensure_output_dir(info.input_path)

    # Check the existences of body.adoc and styles.css and build HTML document
    required_files_existed = check_required_files(for_html = True, common_info = info, html_info = info)
    if (required_files_existed["result"] == SUCCESS):
        args = [
            info.build_html_tool,
            f"--safe-mode={info.safe_mode}",
            "-a", f"stylesdir={info.html_style_path}",
            "-a", f"stylesheet={info.html_style}",
            "-o", f"{info.output_file}",
            f"{info.input_path}/{info.asciidoc_file}"
        ]

        result = run_cmd(args)
    else:
        result = (required_files_existed["result"], required_files_existed["message"])

    """
    End of function
    """

    # Return result
    return result

#==========================================================================================================
# Function:     build_pdf
# Description:  Build document in PDF format.
# Retval:       Info of build result.
#==========================================================================================================
def build_pdf(
) -> tuple[int, str]:  # Type of return value
    """
    Start of function
    """

    # Get PDF information
    info = PDF_Info()

    # Check foler doc existence and create it if needed
    ensure_output_dir(info.input_path)

    # Check the existences of body.adoc and styles.css and build PDF document
    required_files_existed = check_required_files(for_html = False, common_info = info, pdf_info = info)
    if (required_files_existed["result"] == SUCCESS):
        args = [
            info.build_pdf_tool,
            f"--safe-mode={info.safe_mode}",
            "-a", f"pdf-themesdir={info.pdf_themes_path}",
            "-a", f"pdf-theme={info.pdf_theme}",
            "-o", f"{info.output_file}",
            f"{info.input_path}/{info.asciidoc_file}"
        ]

        result = run_cmd(args)
    else:
        result = (required_files_existed["result"], required_files_existed["message"])

    """
    End of function
    """

    # Return result
    return result

#==========================================================================================================
# Function:     build_target
# Description:  Helper to build target.
# Retval:       Info of build result.
#==========================================================================================================
def build_target(
        condition: bool,                            # Condition to check
        build_func: Callable[[], tuple[int, str]],  # Function to call and return tubple[int, str]
        tag: str,                                   # Tag: "HTML" or "PDF"
        result: bool,                               # Current result
        logs: list[tuple[str, int, str]],           # Result log
) -> bool:  # Type of return value
    """
    Start of function
    """

    # Build the selected target and update result log
    if (True == condition):
        status, message = build_func()
        result &= (SUCCESS == status)
        logs.append((tag, status, message))

    """
    End of function
    """

    # Return result
    return result

#==========================================================================================================
# Create Qt pages
#==========================================================================================================
#==========================================================================================================
# Class:        UsagePage
# Description:  A wizard page that shows usage instructions to the user.
# Retval:       None.
#==========================================================================================================
class UsagePage(QWizardPage):
    """
    Start of class
    """

    """A wizard page that shows usage instructions to the user."""

    def __init__(self):
        # Call the base-class constructor so the QWizardPage internals are set up
        super().__init__()

        # Set the page title shown by the QWizard header.
        self.setTitle("Usage Guidelines")

        # Create a vertical layout and attach it to this page (self) as the main layout
        # This is equivalent to: layout = QVBoxLayout(); self.setLayout(layout)
        layout = QVBoxLayout(self)

        # Create a text label containing multi-line instructions
        # Adjacent string literals are concatenated by Python at compile time
        label = QLabel(
            "Users should confirm these items:\n\n"
            "  [1] styles.css (if build HTML) and theme.yml (if build PDF) are located one directory level (../) above this Python script\n"
            "  [2] body.adoc is located in ./doc/ folder (one level below this Python script)\n\n"
            "Click Next to choose which format(s) to build (HTML/PDF)."
        )

        # Enable word wrapping so long lines automatically wrap within the label width
        label.setWordWrap(True)

        # Add the label widget to the page's layout so it becomes visible and managed
        layout.addWidget(label)

    """
    End of class
    """

#==========================================================================================================
# Class:        SelectBuildPage
# Description:  A wizard page that creates checkboxs of options to build.
# Retval:       None.
#==========================================================================================================
class SelectBuildPage(QWizardPage):
    """
    Start of class
    """

    """A wizard page that creates checkboxs of options to build."""

    def __init__(self):
        # Call the base-class constructor so the QWizardPage internals are set up
        super().__init__()

        # Set the page title shown by the QWizard header
        self.setTitle("Select Output Formats")

        # Create unticked checkboxes with their names
        self.cb_html = QCheckBox("Build HTML")
        self.cb_pdf  = QCheckBox("Build PDF")

        # Create a vertical layout and attach it to this page (self) as the main layout
        layout = QVBoxLayout(self)

        # Add widgets vertically (from top to bottom) to the page
        # Vertically because of layout created using QVBoxLayout
        layout.addWidget(QLabel("Please select one or both formats:"))
        layout.addWidget(self.cb_html)
        layout.addWidget(self.cb_pdf)

    # Override of QWizardPage.validatePage()
    # validatePage(), a method that's called when "Next" or "Finish" button is clicked
    def validatePage(self) -> bool:
        result = True

        # When no options are taken
        if (False == self.cb_html.isChecked()) and (False == self.cb_pdf.isChecked()):
            QMessageBox.warning(self, "Nothing selected", "Please select at least one format to build.")
            result = False
        else:
            logs = []

            # Build HTML
            result = build_target(self.cb_html.isChecked(), build_html, "HTML", result, logs)

            # Build PDF
            result = build_target(self.cb_pdf.isChecked(), build_pdf, "PDF", result, logs)

            # Show summary
            # Check the entire log if there is a text format (tag, status, message) like ("PDF", status, message) and append the msg_lines
            # msg_lines should be like [PDF] SUCCESS or [HTML] FAILURE\n"..."
            msg_lines = []
            for (tag, status, message) in logs:   # tag: "HTML" or "PDF"
                status_msg = "SUCCESS" if (SUCCESS == status) else "FAILED"
                msg_lines.append(f"[{tag}] {status_msg}\n{message}\n")

            # Print the icon according to the result
            icon = QMessageBox.Icon.Information if (True == result) else QMessageBox.Icon.Critical
            QMessageBox(icon, "Build Results", "\n".join(msg_lines), QMessageBox.StandardButton.Ok, self).exec()
        
        # Return result
        return result

    """
    End of class
    """

#==========================================================================================================
# Class:        BuildWizard
# Description:  Build Qt wizard: window, pages.
# Retval:       None.
#==========================================================================================================
class BuildWizard(QWizard):
    """
    Start of class
    """

    def __init__(self):
        super().__init__()

        # Set window title
        self.setWindowTitle("Build User Manual")

        # Create pages
        self.addPage(UsagePage())
        self.addPage(SelectBuildPage())

        # Resize pages
        self.resize(680, 420)
    
    """
    End of class
    """

#==========================================================================================================
# Main function
#==========================================================================================================
def main():
    # Create handle of Qt application
    app = QApplication(sys.argv)

    # Create Qt windows and show
    wiz = BuildWizard()
    wiz.show()

    # Exit Qt application
    sys.exit(app.exec())

# Only run the app when this file is executed directly.
if __name__ == "__main__":
    print(f"{Fore.LIGHTRED_EX}Prequisites{Style.RESET_ALL}: Python >= {Fore.LIGHTGREEN_EX}3.10.x{Style.RESET_ALL}")
    main()

#==========================================================================================================
# End of file
#==========================================================================================================
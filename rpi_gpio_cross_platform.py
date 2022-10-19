# pip install git+https://github.com/sn4k3/FakeRPi
import importlib.util
try:
    importlib.util.find_spec('RPi.GPIO')
    print("Is Raspberry PI")
    import RPi.GPIO as GPIO
except ImportError:
    """
    import FakeRPi.GPIO as GPIO
    OR
    import FakeRPi.RPiO as RPiO
    """
    print("Not Raspberry PI")
    import FakeRPi.GPIO as GPIO

# Do your code here

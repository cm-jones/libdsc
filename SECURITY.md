# Security Policy

## Supported Versions

We actively support the following versions of libdsc with security updates:

| Version | Supported          |
| ------- | ------------------ |
| 0.1.x   | :white_check_mark: |

## Reporting a Vulnerability

We take the security of libdsc seriously. If you discover a security vulnerability, please follow these steps:

### How to Report

1. **Do NOT create a public GitHub issue** for security vulnerabilities
2. Send an email to the maintainers with details about the vulnerability
3. Include the following information in your report:
   - Description of the vulnerability
   - Steps to reproduce the issue
   - Potential impact
   - Suggested fix (if you have one)

### What to Expect

- **Acknowledgment**: We will acknowledge receipt of your vulnerability report within 48 hours
- **Initial Assessment**: We will provide an initial assessment within 5 business days
- **Updates**: We will keep you informed of our progress throughout the investigation
- **Resolution**: We aim to resolve critical vulnerabilities within 30 days

### Security Considerations

libdsc is a C library that handles memory management and user data. Common security concerns include:

- **Memory Safety**: Buffer overflows, use-after-free, double-free
- **Input Validation**: Handling of invalid parameters and edge cases
- **Integer Overflow**: Size calculations and capacity management
- **Denial of Service**: Resource exhaustion attacks

### Responsible Disclosure

We follow responsible disclosure practices:

1. We will work with you to understand and resolve the issue
2. We will credit you in our security advisory (unless you prefer to remain anonymous)
3. We ask that you do not publicly disclose the vulnerability until we have had a chance to address it
4. We will coordinate the timing of public disclosure with you

### Security Best Practices for Users

When using libdsc in your applications:

1. **Validate Input**: Always validate data before passing it to libdsc functions
2. **Error Handling**: Check return values and handle errors appropriately
3. **Memory Management**: Ensure proper cleanup of libdsc objects
4. **Bounds Checking**: Verify indices before accessing container elements
5. **Compiler Flags**: Use appropriate compiler security flags (e.g., `-fstack-protector`, `-D_FORTIFY_SOURCE=2`)

### Security Testing

libdsc undergoes regular security testing including:

- Static analysis with clang-static-analyzer
- Dynamic analysis with AddressSanitizer and UndefinedBehaviorSanitizer
- Fuzzing of public APIs (planned)
- Regular security audits of critical code paths

## Contact

For security-related inquiries, please contact the maintainers through the project's GitHub repository.

Thank you for helping keep libdsc secure!
